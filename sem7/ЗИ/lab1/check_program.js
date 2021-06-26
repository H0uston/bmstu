const lib = require('./script');

function checkSystem(fileName) {
    const UUID = lib.executeCommand("system_profiler SPHardwareDataType | awk '/UUID/ { print $3; }'");
    const hash = lib.getHash(UUID, 'base64');
    const key = lib.readFromFile(fileName);
    if (key === hash) {
        console.log("Hashes are the same!");
    } else {
        console.log("Hashes are different!");
    }
}

function main(argv) {
    const fileName = argv[2];

    if (fileName === undefined || fileName === null) {
        console.log("Wrong CMD! node check.js file_name_to_read");
        return;
    }

    checkSystem(fileName);
}

main(process.argv);