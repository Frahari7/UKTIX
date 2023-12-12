const fs = require("fs");
const nodemailer = require("nodemailer");

function main(){
    let fileContent = fs.readFileSync("./bin/data/Ticket.tix");
    let fileObject = JSON.parse(fileContent);
    sendMail(fileObject.email, fileObject.text);
};

function readFile(filePath) {
    if(!fs.existsSync(filePath)) {
        console.log("Error: File not exist");
        return;
    }
    let content = fs.readFileSync(filePath, err => {
        if (err) throw err;
    });
    return content;
}

function sendMail(mailTo, mailText) {
    const transporter = nodemailer.createTransport({
        service: "gmail",
        auth: {
            user: "uktjaya@gmail.com",
            pass: "apa lu liat liat"
        }
    });

    const mailOptions = {
        from: "uktjaya@gmail.com",
        to: mailTo,
        subject: "UKTix Ticket",
        text: mailText
    };

    transporter.sendMail(mailOptions, function(err) {
        if(err) {
            console.log("     ┌──────────────────────────────────────┐\n"
                      + "     │            \x1b[31mEmail not found\x1b[0m           │\n"
                      + "     │     Press any key to continue...     │\n"
                      + "     └──────────────────────────────────────┘");
            return;
        } else {
            console.log("     ┌──────────────────────────────────────┐\n"
                      + "     │        \x1b[92mTickets have been sent\x1b[0m        │\n"
                      + "     │     Press any key to continue...     │\n"
                      + "     └──────────────────────────────────────┘");
        }
    });
}

main();
