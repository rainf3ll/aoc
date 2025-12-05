import * as fs from 'fs';

const content = fs.readFileSync('in.txt', 'utf-8');
const items = content.trimEnd().split('\n');
const ranges =
    items.slice(0, items.findIndex((element: string) => element === ""))
        .map((r: string) => r.split('-').map(Number))
        .sort((a: [number, number], b: [number, number]) => a[0] - b[0])
        .reduce((acc: [number, number][], val: [number, number]) => {
            if (acc.length === 0) {
                acc.push(val);
            } else {
                const last = acc[acc.length - 1];
                if (val[0] <= last[1]) {
                    last[1] = Math.max(last[1], val[1]);
                } else {
                    acc.push(val);
                }
            }
            return acc;
        }, []);

const indexes = items.slice(items.findIndex((element: string) => element === "") + 1).map(Number);

function inRange(x: number): boolean {
    return ranges.some(([start, end]) => x >= start && x <= end);
}

function solve1(): number {
    let result: number = 0;
    for (let i = 0; i < indexes.length; i++) {
        if (inRange(indexes[i])) {
            result++;
        }
    }
    return result;
}

function solve2(): number {
    let result: number = 0;
    for (let i = 0; i < ranges.length; i++) {
        result += ranges[i][1] - ranges[i][0] + 1;
    }
    return result;
}

console.log("silver: " + solve1());
console.log("gold: " + solve2())
