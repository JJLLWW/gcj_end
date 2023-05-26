const process = require("process");

// how hard would a typescript refactor be?

async function ReadStdin() {
    process.stdin.setEncoding("utf-8");
    let all_input = "";
    for await (const chunk of process.stdin) {
        all_input += chunk;
    }
    return all_input;
}

if(require.main === module) {
    // read from stdin if called from top level node.
    ReadStdin().then((text) => {
        TaskMain(text);
    });
} else {
    ;
}

// min number of letters to delete in P to get I or IMPOSSIBLE.
// - len(P) < len(I) means IMPOSSIBLE.
// - always same number of letters deleted, so either IMPOSSIBLE or len(I) - len(P).
function SolveCase(I, P) {
    if(P.length < I.length) {
        return "IMPOSSIBLE";
    }
    let j = 0;
    for(let i=0; i<P.length; ++i) {
        if(P[i] == I[j]) {
            ++j;
        }
    }
    return (j == I.length) ? (P.length - I.length) : "IMPOSSIBLE";
}

function TaskMain(text) {
    const lines = text.split("\n");
    const T = parseInt(lines[0], 10);
    for(let i = 1, t = 1; t <= T; ++t) {
        const I = lines[i++];
        const P = lines[i++];
        const Result = SolveCase(I, P);
        console.log(`Case #${t}: ${Result}`);
    }
}

exports.TaskMain = TaskMain;