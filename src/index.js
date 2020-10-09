const app = require('./app');
const ora = require('ora')
const color = require('colors')
const jsome = require('jsome')

const port = process.env.PORT || 5000;
app.listen(port, () => {
    console.log('[ SimpleSmarthome By FajarTheGGman ]'.bgBlue)
    jsome({
        Coder: "FajarTheGGman",
        Github: "FajarTheGGman",
        Twitter: "@Kernel024",
        Instagram: "@FajarTheGGman"
    })

    ora(console.log('[!] Server Runnning at port : '.rainbow + port )).start()
});
