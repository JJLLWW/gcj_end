// is there some way a module can tell if it's been imported as a module?

if(require.main === module) {
    console.log("CALLED DIRECTLY");
} else {
    console.log("AS MODULE");
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

    return "IMPOSSIBLE";
}

function TaskMain(text) {
    console.log(text);
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