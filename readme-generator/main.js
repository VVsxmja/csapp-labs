import * as fs from 'fs/promises'
import * as path from 'path'
import { Octokit } from 'octokit'

/* parse result */

const resultPath = '../results'

class Score {
    constructor(score, total, other) {
        this.score = score
        this.total = total
        this.other = other
        this.other.toString = function () {
            let r = ''
            if (this.warning > 0) {
                r += `, ⚠️ ${this.warning} warning(s)`
            } else {
                r += `, ✅ No warning`
            }
            return r
        }
    }
    toString() {
        return `${this.score} / ${this.total}${this.other}`
    }
    get done() {
        return this.score === this.total
    }
}

const resultObjects = [
    {
        name: 'Data Lab',
        async autoCheck() {
            const content = await fs.readFile(path.join(resultPath, 'data-lab-test.txt'), {
                encoding: 'utf-8'
            })
            const result = /Total points: (?<score>\d+)\/(?<total>\d+)/.exec(content)
            const checkContent = await fs.readFile(path.join(resultPath, 'data-lab-check.txt'), {
                encoding: 'utf-8'
            })
            this.score = new Score(parseInt(result.groups.score), parseInt(result.groups.total), {
                warning: checkContent.match(/dlc:bits.c:\d+:.*: Warning:/g)?.length
            })
        }
    },
    { name: 'Bomb Lab' },
    { name: 'Attack Lab' },
    { name: 'Buffer Lab (IA32)' },
    { name: 'Architecture Lab' },
    { name: 'Architecture Lab (Y86)' },
    { name: 'Cache Lab' },
    { name: 'Performance Lab' },
    { name: 'Shell Lab' },
    { name: 'Malloc Lab' },
    { name: 'Proxy Lab' },
]

if (!fs.access('../results')) {
    console.error('Result directory not exist')
    process.exit(-1)
}

for (const target of resultObjects) {
    if (!target.autoCheck) {
        console.log(`Auto check of ${target.name} not implemented yet`)
    } else {
        try {
            await target.autoCheck()
            console.error(target.score)
        } catch (e) {
            console.error(`Failed parsing result of ${target.name}: \n`, e)
        }
    }
}

let logParsed = 'Parsed result:\n'
let finalMarkdown = '|   |Lab|Score|\n|---|---|---|\n'

for (const target of resultObjects) {
    console.log(target)
    if (!!target.score) {
        logParsed += `\t${target.name}:\t ${target.score}\n`
        finalMarkdown += `| ${target.score.done ? '✅' : '🤔'} | ${target.name} | **\`${target.score}\`** | \n`
    } else {
        logParsed += `\t${target.name}:\t Not parsed\n`
        finalMarkdown += `| ⏳ | ${target.name} | *\`Not implemented\`* | \n`
    }
}

console.log(logParsed)


const octokit = new Octokit({ auth: process.env.TOKEN })

const repo = process.env.REPO

console.log(`Updating readme.md of ${repo}`)

const readmeData = (await octokit.request(`GET /repos/${repo}/readme`)).data

const readme = Buffer.from(readmeData.content, readmeData.encoding).toString()

const insertPoint = 'score'
const beginPattern = `<!-- ${insertPoint.trim()} begin -->`
const endPattern = `<!-- ${insertPoint.trim()} end -->`

const beginIndex = readme.indexOf(beginPattern)
const endIndex = readme.indexOf(endPattern)

if (beginIndex === -1 || endIndex === -1) {
    console.error('Insert point not found. Please add '
        + beginPattern + ' and ' + endPattern
        + ' to where you want AutoGrade to insert data')
    process.exit(-1)
} else {
    const newReadme = readme.substring(0, beginIndex + beginPattern.length) + '\n'
        + finalMarkdown + readme.substring(endIndex)
    await octokit.request(`PUT /repos/${repo}/contents/{path}`, {
        path: readmeData.path,
        message: `🚀 Automatically update ${readmeData.name} by AutoGrade`,
        content: Buffer.from(newReadme).toString('base64'),
        sha: readmeData.sha,
    })
}