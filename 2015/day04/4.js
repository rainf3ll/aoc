const crypto = require('crypto');
const fs = require('fs');

const data = fs.readFileSync("in.txt", "utf-8");

let num = 1;
let currentKey = data.toString().trim() + num.toString().trim();

let silverDone = false;
let goldDone = false;

while (!silverDone || !goldDone) {
    let hash = crypto.createHash("md5").update(currentKey).digest("hex");
    if (!silverDone && hash.startsWith("00000")) {
        silverDone = true;
        console.log("Silver: " + num);
    }
    if (!goldDone && hash.startsWith("000000")) {
        goldDone = true;
        console.log("Gold: " + num);
    }
    num++;
    currentKey = data.toString().trim() + num.toString().trim();
}
