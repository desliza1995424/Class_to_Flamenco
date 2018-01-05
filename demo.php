<!doctype html>
<html>
<head>
    <meta charset="utf-8" />
	<!-- Compiled and minified CSS -->
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.6/css/materialize.min.css">
	 
	<!--material css-->
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
	
	<!-- jQuery -->
    <script type="text/javascript" charset="utf8" src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
	
    <!--material js-->
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.6/js/materialize.min.js"></script>
	
	<title>From Classic to Flamenco</title>
	
	<style>
		header, main{
			font-family:\5FAE\8EDF\6B63\9ED1\9AD4,Microsoft JhengHei,MingLiU,sans-serif;
			font-size:150%;
		}
		#about_link li{
			display:inline;
		}
		#tabs_list li{
			list-style-type: circle;
			margin-left : 25px;
		}
		<!-- Nav -->
		#side-nav{
			list-style-type: none;
			margin-top: 100px;
			padding: 0;
		}
		#nav-title{
			display:block;
			color: white;
			padding: 8px 16px;
		}
		#side-nav li a{
			display:block;
			color: #000;
			padding: 8px 16px;
			text-decoration: none;
		}
		.page-footer{
			line-height:30%;
		}
	</style>
</head>

<body>
	<header>
		<nav>
			<div id="nav-header" class="nav-wrapper z-depth-1 blue-grey lighten-1">
				<div class="row">
					<div class="col s10">
						<a href="index.php" class="breadcrumb"><span class="white_text">&nbsp;主頁面</span></a>
						<!--<a class="breadcrumb"><span class="white_text">demo頁面</span></a>-->
					</div>
					<div class="col s2">
						<!-- Dropdown Trigger -->
						<a class='dropdown-button transparent' href='#' data-activates='dropdown1'><span class="white_text">&nbsp&nbsp&nbsp&nbsp&nbspMenu▽</span></a>
					</div>
				</div>
			</div>
		</nav>
		<!-- Dropdown Structure -->
		<ul id='dropdown1' class='dropdown-content'>
			<li id="type1"><a href="http://google.com" class="blue-grey-text text-darken-2">PPT</a></li>
			<li id="type2"><a href="http://google.com" class="blue-grey-text text-darken-2">Questionaire</a></li>
			<li id="type3"><a href="http://google.com" class="blue-grey-text text-darken-2">About</a></li>
		</ul>
	</header>
	<div class="container">
			<div id="divLoading" >
			<img src="images/infinity.gif"style="vertical-align:middle;padding:6px"/>
			<h3> 作曲中，請稍候...</h3>
		</div>
	
<?php
	error_reporting(E_ALL ^ E_NOTICE);
	if($_GET["human"]!="on")
	{
?>
		<h2>OOPS !!</h2>
		<p>please select the box of	<b>"I am a human and not a robot"</b>, thank you~.	</p>
		<font size=4><a href="index.php"><br/>previous page</a></font>		
		<br/><br/><br/><br/><br/><br/>
<?php
	}
	else if(empty($_GET["username"])){
?>
		<h2>OOPS !!</h2>
		<p>You haven't enter your name. <br/>please go back to <a href='index.php'>previous page</a> and enter again.</p>
		<br/><br/><br/><br/><br/><br/>
		
		
		<script> 
			src='http://www.midijs.net/lib/midi.js'
		</script>
		
<?php
	}
	else if(Is_numeric($_GET["category"]))
	{
		
		$SongName = "";
		$input_file = "";
		
		if($_GET["track"]==1)
		{
			$SongName = "star";
			$input_file = "star";
		}	
		else if($_GET["track"]==2)
		{
			$SongName = "song2";
			$input_file = "song2";
		}	
		else if($_GET["track"]==3)
		{
			$SongName = "song3";
			$input_file = "song3";
		}	
		else if($_GET["track"]==4)
		{
			$SongName = "song4";
			$input_file = "song4";
		}	
			echo "<h4><span class='red-text'>".$_GET["username"]."</span>, welcome,<br /> Please enjoy the <strong>" .$SongName. "</strong>.</h4><br/>";
			
			$filename = "bat.bat";  
			$file = fopen($filename, "w");         
			fwrite($file, "del flamenco.mid\n");     
			fwrite($file, "del evo.txt\n");     
			fwrite($file, "start  /wait flamenco ". $input_file); 
			fwrite($file, "\nstart  /wait t2mf evo.txt EVO.MID\n"); 
			fwrite($file, "rename EVO.MID flamenco.mid\n");
			fclose($file);                                
			
			shell_exec('bat.bat');
	
?>
				
			<script src='http://www.midijs.net/lib/midi.js'></script>
			<script>
				function play_midi_EVO(){
					MIDIjs.play('flamenco.mid');
					}
				function stop_midi_EVO(){
					MIDIjs.stop('flamenco.mid');
					}
				var input_file = "<?php echo $input_file.'.mid';?>"
				console.log("file="+input_file);
				function play_midi_RAN(){
					MIDIjs.play(input_file);
					}
				function stop_midi_RAN(){
					MIDIjs.stop(input_file);
					}
				function init( ) {	
					_oTag = document.getElementById("divLoading");
					_oTag.style.display = "none";  // hide it.
				}
			</script>
				
			<h3> Initial music</h3>
			<button class="btn wave-effect" onclick="play_midi_RAN()"><i class="material-icons right">play_circle_filled</i>PLAY</button>			
			<button class="btn wave-effect" onclick="stop_midi_RAN()"><i class="material-icons right">pause_circle_filled</i>STOP</button>
<?php
			echo "<br/><br/><a id='input_file' name='".$input_file.".mid' href=".$input_file.".mid><h5>Press here download the ".$input_file." music </h5></a>"
?>
			
			<h3> Evolution music</h3>
			<button class="btn wave-effect" onclick="play_midi_EVO()"><i class="material-icons right">play_circle_filled</i>PLAY</button>			
			<button class="btn wave-effect" onclick="stop_midi_EVO()"><i class="material-icons right">pause_circle_filled</i>STOP</button>
			<br/><br/><a href="flamenco.mid"><h5>Press here download the evolution music </h5></a>
			
		
<?php
	}
	else 
	{
		echo "<h4>YET select your composer.</h4><br/>";
		echo "<h5>Please press <a href='index.php'>previous page</a></h5><br/><br/><br/><br/><br/><br/><br/><br/>";
		
	}	
?>
			<script>
			function init( ) {	
							_oTag = document.getElementById("divLoading");
							_oTag.style.display = "none";  // hide it.
							}
		
							if (window.attachEvent) {
							window.attachEvent('onload', init);
							} else {
							window.addEventListener('load', init, false);
							}
			</script>
	
	<br/><br/><br/>
		<hr/>
		
		<footer class="page-footer transparent">
          <div class="container">
            <div class="row">
			  <div class="col l4 m4 push-m8 hide-on-small-only">
				<img class="responsive-img" src="./images/music.jpg"/>
			  </div>
              <div class="col l8 m8 s12 pull-m4">
				<ul id="about_link">
                  <li><a class="orange-text text-darken-4" href="https://www.cs.ccu.edu.tw/">資訊工程學系</a></li>
				  <li> | </li>
                  <li><a class="orange-text text-darken-4" href="https://cilab.cs.cu.edu.tw/">計算型智慧實驗室</a></li>
                </ul>
                <p class="grey-text text-darken-3">Advisor: Chuan-Kang Ting</p>
				<p class="grey-text text-darken-3">Member: Yu-Mei Shih, Chun-Ting Ye, Ding-Yuan Chen,</p>
				<p class="grey-text text-darken-3">Li-Hsuan Hsieh</p>
              </div>
            </div>
          </div>
		  
          <div class="footer-copyright">
            <div class="container">
				<span class="black-text">National Chung Cheng University, Taiwan &nbsp; || &nbsp;<a class="brown-text" href="http://www.ccu.edu.tw/">國立中正大學</a></span>
				<span id="current_date" class="grey-text text-darken-2 right"></span>
            </div>
          </div>
        </footer>
	</div>
	
	<script>
		$(document).ready(function(){
			
			var fullDate = new Date();
			//console.log(fullDate);
			var twoDigitMonth = (fullDate.getMonth()+1);
			var twoDigitDay = fullDate.getDate();
			var currentDate = "最後更新:" + fullDate.getFullYear() + "-" + twoDigitMonth + "-" + twoDigitDay;
			console.log(currentDate);
			$("#current_date").text(currentDate);
			
			//$("body").css("background-image","url('./Image/Language_bg.jpg')");
			$(".tabs .indicator").css("background-color","orange");
			
			$('.dropdown-button').dropdown({
				constrain_width: false, // Does not change width of dropdown to that of the activator
				belowOrigin: true, // Displays dropdown below the button
			});
			
			$('.paper_type').click(function (){
				localStorage.setItem("paper_type", $(this).text());
			});
		});
          
	</script>
	<!--script
	<script src="assets/js/skel.min.js"></script>
	<script src="assets/js/util.js"></script>
	<script src="assets/js/main.js"></script>-->
</body>
</html>