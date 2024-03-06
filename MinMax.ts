// Enter the array elements separated by spaces: 66.7 44.4 44.3 2 55.7
// Min Max is:  { min: 2, max: 66.7 }

import * as readline from 'readline';

type MinMaxProps = {
    min: number;
    max: number;
}

function FindMinMax(a: number[], low: number, high: number): MinMaxProps {
    if (low === high) {
        return { max: a[low], min: a[low] } as MinMaxProps;
    }
    else if (low === high - 1) {
        if (a[low] < a[high]) {
            return { max: a[high], min: a[low] } as MinMaxProps;
        } else {
            return { max: a[low], min: a[high] } as MinMaxProps;
        }
    }
    else {
        const mid: number = Math.floor((low + high) / 2)
        const l: MinMaxProps = FindMinMax(a, low, mid);
        const r: MinMaxProps = FindMinMax(a, mid + 1, high);
        var final: MinMaxProps = { min: 0, max: 0 };
        if (l.max > r.max) {
            final.max = l.max;
        } else {
            final.max = r.max;
        }
        if (l.max < r.min) {
            final.min = l.min;
        }
        else {
            final.min = r.min;
        }
        return final;
    }
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Enter the array elements separated by spaces: ', (input) => {
    const a = input.split(' ').map(Number);
    const minMax = FindMinMax(a, 0, a.length - 1);
    console.log("Min Max is: ", minMax);
    rl.close();
});