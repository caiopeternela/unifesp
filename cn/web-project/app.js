const express = require("express")
const app = express()

app.set("view engine", "ejs")
app.set("trust proxy", true)

app.get("/", (req, res) => {
    date = new Intl.DateTimeFormat("en-US", { dateStyle: "full", timeStyle: "long", timeZone: "America/Sao_Paulo" }).format(new Date())
    res.render("index", { date: date, ip: req.ip })
})

app.listen(3000, () => {
    console.log("Server is running on http://localhost:3000")
})