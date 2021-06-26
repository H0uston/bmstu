function executeCommand(command) {
    try {
        const childProcess = require('child_process');
        const result = childProcess.execSync(command).toString();
        return result;
    } catch (e) {
        throw e;
    }
}

function getHash(string, algorithm='base64') {
    try {
        const crypto = require('crypto');
        const hash = crypto.createHash('sha256').update(string).digest(algorithm);
        return hash;
    } catch (e) {
        throw e;
    }
}

function writeToFile(string, fileName='key') {
    try {
        const fs = require('fs');
        fs.writeFileSync(fileName, string, function (err) {
            if (err) {
                throw new Error("Can't create file!");
            }
            console.log("Key was created.");
        });
    } catch (e) {
        throw e;
    }
}

function readFromFile(fileName, extension='utf8') {
    try {
        const fs = require('fs');
        const text = fs.readFileSync(fileName, extension, function (err, data) {
            if (err) {
                throw new Error(err.message);
            }
            console.log("File was read");
        });
        return text;
    } catch(e) {
        throw e;
    }
}

module.exports = {executeCommand, readFromFile, getHash, writeToFile};