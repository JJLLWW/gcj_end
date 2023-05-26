"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
const fs = require("fs");
const task1 = require("./task1");
const task2 = require("./task2");
const task3 = require("./task3_2");
// must be better way.
const tasks = new Array();
tasks[0] = task1;
tasks[1] = task2;
tasks[2] = task3;
function DoTask(TaskID) {
    return __awaiter(this, void 0, void 0, function* () {
        const TaskPath = `./task${TaskID}.txt`;
        const file = yield fs.promises.open(TaskPath);
        const text = yield file.readFile({ encoding: "utf8" });
        tasks[TaskID - 1].TaskMain(text);
    });
}
function main() {
    return __awaiter(this, void 0, void 0, function* () {
        DoTask(3);
    });
}
main();
