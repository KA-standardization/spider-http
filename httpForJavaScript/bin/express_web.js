const express = require("express");
// const nocache = require('nocache');



const app = express();
// app.use(nocache());
const workspaceFolder = "/spider-http/httpForJavaScript";

app.get("/", (req, res) => {
  res.end("this api model is POST");
});

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.post("/encrypt", (req, res, next) => {
  function tmp() {
    let func1 = require(`${workspaceFolder}` +
      "/src/zhEncrypt.js");
    let rdata = func1.Jagd(req.body.J);
    return rdata;
  }
  res.end(tmp());
});


app.listen(21023, () => console.log(`Example app listening on port 21023!`));
