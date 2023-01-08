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


const { SerialPort } =  require('serialport');

SerialPort.list().then(d=>console.log(d.filter(d => d.path.includes('ACM'))));

const serialport = new SerialPort({ path: '/dev/ttyACM0', baudRate: 15200 })

// setInterval(() => {
while(1) {
    const byte = serialport.read();
    if (byte) {
        console.log('movie', byte[0], bytes[byte[0]]);
        serialport.write(Uint8Array.from([bytes[byte[0]]]));
    }
}
// });
