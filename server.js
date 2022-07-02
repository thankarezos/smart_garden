var express = require('express');
var app = express();
const bodyParser = require("body-parser");
const router = express.Router();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

var intervalS = 10000;

app.get('/status', function (req, res) {
   var obj = {};

   res.end(JSON.stringify(
      { 
        interval: intervalS
      }
   ,null,4));
})

var soilSensitivity = 750

router.post('/handle',(req,res) => {

   var soilSensor = req.body.soil;
   var isWet;
   
   
   
   if(soilSensor != null && soilSensor >=0 && soilSensor <=1024){

      if(soilSensor < soilSensitivity ){
         isWet = "Yes";
      }
      else{
         isWet = "No";
      }

      res.end(succsess);
      console.log(soilSensor + " " + isWet);
   }
   else{
      res.status(400);
      res.end(BadR);
   }
   
});


app.use("/", router);

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port
   console.log("Example app listening at http://%s:%s", host, port)
})

const books = JSON.stringify([
    { 
		title: "The Alchemist", 
		author: "Paulo Coelho", 
		year: 1988 },
    { title: "The Prophet", author: "Kahlil Gibran", year: 1923 }
],null,4);

const succsess = JSON.stringify(
   { 
     status: "succsess"
   }
,null,4);

const fail = JSON.stringify(
   { 
     status: "fail"
   }
,null,4);

const BadR = JSON.stringify(
   { 
     status: "Bad Request"
   }
,null,4);