var express = require('express');
var app = express();
const bodyParser = require("body-parser");
const router = express.Router();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/test', function (req, res) {
   res.end(books);
})
router.post('/handle',(req,res) => {

   var soilSensor = req.body.soil;

   
   if(soilSensor != null && soilSensor >=0 && soilSensor <=1024){
      res.end(succsess);
      console.log(req.body);
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