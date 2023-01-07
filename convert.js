const fs = require('fs');
const inputs = fs.readFileSync('./Input Log.txt', 'utf8');
const _pad = 'UDLRSsBA';
const bytes = [];
inputs.split('\n').forEach(line => {
    if (line.startsWith('|')) {
        const input = line.match(/\|(.{8})\|/)[1];
        const byteStr = [...input].map(d => d == '.' ? 0 : 1).join('');
        const byte = parseInt(byteStr, 2);
        bytes.push(byte);
    }
});

console.log(JSON.stringify(bytes.slice(0,600)));
console.log(bytes.length);
