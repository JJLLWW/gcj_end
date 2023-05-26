const process = require("process");

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

function ReadInts(line) {
    const words = line.split(" ");
    const nums = [];
    words.forEach(word => {
        nums.push(parseInt(word, 10));
    });
    return nums;
}

function SolveCase(CaseData) {
    ;
    return "IMPOSSIBLE";
}

function TaskMain(text) {
    const lines = text.split("\n");
    const T = parseInt(lines[0], 10);
    for(let i=1, t=1; t <= T; ++t) {
        // should be a type, so less room for error if had to scale.
        let CaseData = {
            M : 0, R : 0, N : 0, X : []
        };
        [CaseData.M, CaseData.R, CaseData.N] = ReadInts(lines[i++]);
        CaseData.X = [...ReadInts(lines[i++])];
        Result = SolveCase(CaseData);
        console.log(`Case #${t}: ${Result}`);
    }
}

exports.TaskMain = TaskMain;