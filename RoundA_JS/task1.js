const process = require("process");

// async function ReadStdin() {
//     process.stdin.setEncoding("utf-8");
//     let all_input = "";
//     for await (const chunk of process.stdin) {
//         all_input += chunk;
//     }
//     return all_input;
// }

// typescript would objectively make this code better.
function ParseCase(lines, I) {
    // ugh
    Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Nums = lines[I++].split(" ");
    let EncMap = new Map();
    for(let i=0; i<26; ++i) {
        EncMap.set(Alphabet[i], Nums[i]);
    }
    const N = parseInt(lines[I++], 10);
    let words = [];
    for(let i=0; i<N; ++i) {
        words.push(lines[I++]);
    }
    return {
        EncMap : EncMap,
        I : I,
        Words : words
    };
}

function EncodeStr(EncMap, str) {
    let Encoded = "";
    for(char of str) {
        Encoded += EncMap.get(char);
    }
    return Encoded;
}

function Task1Main(text) {
    // maintaining I is pretty disgusting, probably a better way.
    let I = 1;
    const lines = text.split("\n");
    const T = parseInt(lines[0], 10);
    for(let t = 1; t <= T; ++t) {
        let CaseInfo = ParseCase(lines, I);
        I = CaseInfo.I;
        Words = CaseInfo.Words.map((word) => (EncodeStr(CaseInfo.EncMap, word)));
        const UniqueWords = new Set(Words);
        const OutStr = (UniqueWords.size === Words.length ? "NO" : "YES");
        console.log(`Case #${t}: ${OutStr}`);
    }
}

// this wouldn't scale very well.
// exports.ReadStdin = ReadStdin;
exports.TaskMain = Task1Main;