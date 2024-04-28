<?php
	include "connection.php";
    
	// Create connection
    $conn = mysqli_connect($servername, $username, $password, $database);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }
 
    //Get current date and time
    date_default_timezone_set('Asia/Jakarta'); 
	$seminggu = array("Dimance","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi");
	$hari = date("w");
	$hari_ini = $seminggu[$hari];
    //$d = date("Y-m-d");
	$tgl_sekarang = date("ymd");
    //echo " Date:".$d."<BR>";
    $jam_sekarang = date("H:i:s");
 
    if(!empty($_POST['status1'])  && !empty($_POST['status2']) && !empty($_POST['pelanggan']))
    {
    	$status1 = $_POST['status1'];
	$status2 = $_POST['status2'];
    	$pelanggan = $_POST['pelanggan'];
 
	    $sql = "INSERT INTO logs (tanggal, hari, waktu, pelanggan, suhu, ketinggian)
		
		VALUES ('".$tgl_sekarang."',  '".$hari_ini."', '".$jam_sekarang."', '".$pelanggan."', '".$status1."','".$status2."')";
 
		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
 
 
	$conn->close();
?>