const lib = require('./script');

function createKey(fileName="key") {
    const UUID = lib.executeCommand("system_profiler SPHardwareDataType | awk '/UUID/ { print $3; }'");
    const hash = lib.getHash(UUID, 'base64');
    const result = lib.writeToFile(hash, fileName);
    console.log("Key was created.");
}

function main(argv) {
    let fileName = argv[2];

    if (fileName === undefined || fileName === null) {
        fileName = "key";
    }

    createKey(fileName);
}

main(process.argv);