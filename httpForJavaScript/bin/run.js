const express = require("express");

const app = express();
const workspaceFolder = "/spider-http/httpForJavaScript";

app.get("/", (req, res) => {
  res.end("Error request path");
});

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.post("/encrypt", (req, res, next) => {
  function myme() {
    let func = require(`${workspaceFolder}` + "/src/zhEncrypt.js");
    let rdata = func.Jagd(req.body.myme);
    return rdata;
  }
  res.end(myme());
});


app.listen(10247, "0.0.0.0", () => console.log(`Example app listening on port 10247!`));
