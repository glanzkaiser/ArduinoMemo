<!DOCTYPE html>
<html>
<head>
<meta http-equiv="refresh" content="7">
<title>Temperature and Altitude Monitoring</title>
  
</head>


<body>
<style>
#c4ytable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
}
 
#c4ytable td, #c4ytable th {
    border: 1px solid #ddd;
    padding: 8px;
}
 
#c4ytable tr:nth-child(even){background-color: #f2f2f2;}
 
#c4ytable tr:hover {background-color: #ddd;}
 
#c4ytable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #00A8A9;
    color: white;
}
</style>
    
    <div id="cards" class="cards">
	
    <table id="c4ytable" width="700" height="119" align="center" border="2" bordercolor="#000000">
    <tr>  			
	<td width="36"><strong><center>No		</center><strong></td> 
        <td width="90"><strong><center>Date	   	</center><strong></td>
	<td width="90"><strong><center>Day	        </center><strong></td>
        <td width="75"><strong><center>Time		</center><strong></td>
        <td width="130"><strong><center>Name		</center><strong></td>
        <td width="130"><strong><center>Temperature 	</center><strong></td>
	<td width="200"><strong><center>Altitude	</center><strong></td>
                                
    </tr>
    
   <?php
	error_reporting(E_ALL);
   ini_set('display_errors', 1);
	require_once('connection.php');
	$query1="select * from logs ";		
	$result=mysqli_query($conn,$query1);
	
	$no  = 1;
	while($data=mysqli_fetch_array($result))
	{
	
	?>
			<tr>
				<td height="80" align="center"><?php echo $no++ ?></td>
			    	<td align="center"><?php echo $data['tanggal'] ?></td>
				<td align="center"><?php echo $data['hari'] ?></td>
				<td align="center"><?php echo $data['waktu'] ?></td>
				<td align="center"><?php echo $data['pelanggan'] ?></td>
				<td align="center"><?php echo $data['suhu'] ?></td>
				<td align="center"><?php echo $data['ketinggian'] ?></td>
								
		  </td>
        </tr>
    <?php
    }
    ?>
    </table>
 


</body>
</html>