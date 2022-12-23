var express = require('express');
var app = express();
const bodyParser = require("body-parser");
const router = express.Router();
const conn = require(__dirname + '/services/db');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
// app.use(express.static(__dirname + '/public'));


app.get('/status', function (req, res) {

   var deviceID = req.query.deviceID;
   const values = [deviceID];
   if(deviceID != null && deviceID >=0){
      conn.query("SELECT checkinterval FROM status where deviceid=?",[values], function (err, result, fields) {
         
         if (err) {
            res.end(DBerror);
         }
         else{
            if(typeof result[0] !== 'undefined'){
               res.end(JSON.stringify(
                  { 
                  status: "succsess",
                  interval: result[0].checkinterval
                  }
               ,null,4));
            }
            else{
               res.end(JSON.stringify(
                  { 
                     status: "No Device"
                  }
               ,null,4));   
            }
         }
      });
   }
   else{
      res.status(400);
      res.end(BadR);
   }

   
})

router.post('/handle',(req,res) => {

   var soilSensor = req.body.soil;
   var deviceID = req.body.deviceID;
   
   if(soilSensor != null && soilSensor >=0 && soilSensor <=1024 && deviceID !=null && deviceID >= 0){
      conn.query("SELECT count(*) as count FROM status where deviceid=?",deviceID, function (err, result, fields) {
         if (err) {
            res.end(DBerror);
         }
         else{
            if(result[0].count < 1){
               res.end(JSON.stringify(
                  { 
                     status: "No Device"
                  }
               ,null,4));
            }

         }
      });

      
      console.log("soil:" + soilSensor + " [" + DateTime() + "]");

      const values = [soilSensor,deviceID];
      conn.query(
         "INSERT INTO sensors (soil,deviceid) VALUES(?)",
         [values],
         function (err, data, fields) {
            if (err) {
               res.end(DBerror);
            }
            else{
               res.end(succsess);
            }
            
         }
      );

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

function DateTime() {
   let date_ob = new Date();

   // current date
   // adjust 0 before single digit date
   let date = ("0" + date_ob.getDate()).slice(-2);

   // current month
   let month = ("0" + (date_ob.getMonth() + 1)).slice(-2);

   // current year
   let year = date_ob.getFullYear();

   // current hours
   let hours = date_ob.getHours();

   // current minutes
   let minutes = date_ob.getMinutes();

   // current seconds
   let seconds = date_ob.getSeconds();

   // prints date in YYYY-MM-DD format
   // console.log(year + "-" + month + "-" + date);

   // prints date & time in YYYY-MM-DD HH:MM:SS format
   // console.log(year + "-" + month + "-" + date + " " + hours + ":" + minutes + ":" + seconds);
   return year + "-" + month + "-" + date + " " + hours + ":" + minutes + ":" + seconds;   // The function returns the product of p1 and p2
}