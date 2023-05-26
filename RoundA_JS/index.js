const fs = require("fs");
const task1 = require("./task1");
const task2 = require("./task2");

// must be better way.
const tasks = new Array();
tasks[0] = task1;
tasks[1] = task2;

async function DoTask(TaskID) {
    const TaskPath = `./task${TaskID}.txt`
    const file = await fs.promises.open(TaskPath);
    const text = await file.readFile({encoding: "utf8"});
    tasks[TaskID-1].TaskMain(text);
}

async function main() {
    DoTask(2);
}

main();