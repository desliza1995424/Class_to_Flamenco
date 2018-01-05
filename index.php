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
			<li id="type1"><a href="test.pptx" class="blue-grey-text text-darken-2">PPT</a></li>
			<li id="type2"><a href="http://google.com" class="blue-grey-text text-darken-2">Questionaire</a></li>
			<li id="type3"><a href="http://google.com" class="blue-grey-text text-darken-2">About</a></li>
		</ul>
		<div class="container valign-wrapper">
			<div class="center-align">
				<h3><b>ClassFlam: From Classic to Flamenco</b></h3>
				<br/><br/>
			</div>
		</div>
	</header>
	<div class="container">
			<h4>請選擇一首歌曲</h4>
			<form action="demo.php" method="get" id="login_form">
					<div class="row">
						<div class="col s12">
							<input type="text" name="username" id="name" value= "" placeholder="Your name" />
						</div>
					</div>
					<div class="input-field col s16">
						<select id="composer" name="category" transparent>
							<option value="" class="blue-grey-text text-lighten-2">Select your composer~</option>
							<option value="1">Mozart</option>
							<option value="2">Bach</option>
							<option value="3">Haydn</option>
							<option value="4">song 4</option>
						</select>
						<!--<label>Select your song~</label>-->
					</div>
					<br/>
					
					<!--<div class="row">
						<div class="col s12">
							<font size="5"> Tracks <br/></font>
						</div>
					</div>-->
					<div class="tracks track1 row">
						<div class="col s4">
							<input type="radio" id="low" name="track" value = "0" checked>
							<label for="low">Mozart1</label>
						</div>
						<div class="col s4">
							<input type="radio" id="normal" name="track" value = "1">
							<label for="normal">Mozart2</label>
						</div>
						<div class="col s4">
							<input type="radio" id="high" name="track" value = "2">
							<label for="high">Mozart3</label>
						</div>
					</div>
					<div class="tracks track2 row">
						<div class="col s4">
							<input type="radio" id="low_1" name="track" value = "3" >
							<label for="low_1">Bach1</label>
						</div>
						<div class="col s4">
							<input type="radio" id="normal_1"name="track" value = "4">
							<label for="normal_1">Bach2</label>
						</div>
						<div class="col s4">
							<input type="radio" id="high_1" name="track" value = "5">
							<label for="high_1">Bach3</label>
						</div>
					</div>
					<br/><br/>
					<div class="row">
						<div class="col s6">
							<input type="checkbox" id="human" name="human" >
							<label for="human">I am not a robot</label>
						</div>
					</div>
					
					<div class="row">
						<div class="col s8">
							<a class="waves-effect waves-light btn-large white-text blue-grey lighten-1"><i class="material-icons right">send</i><input type="submit" value="submit" /></a>
							<a class="waves-effect waves-light btn-large white-text blue-grey lighten-1"><i class="material-icons right">replay</i><input type="reset" value="reset" /></a>
						</div>
					</div>
					
					<!--<img src="images/infinity.gif" id="gif" style="display: block; margin: 0 auto; width:200px; visibility:  hidden;">
					<img src="images/ch.jpg"  id="image" style="display: block; margin: 0  auto; height:75px;  top:200px;  width: 300px; visibility: hidden;">-->
			</form>
		
		<hr/>
		
		<footer class="page-footer transparent">
          <div class="container">
            <div class="row">
			  <div class="col l4 m4 push-m8 hide-on-small-only">
				<img class="responsive-img" src="./images/guitar.png"/>
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
			$('select').material_select();
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
			
			$('.tracks').hide();
			$('#composer').change(function() {
				$('.tracks').hide();
				var select_value = $('#composer').val();
				$('.track' + select_value).show();/*該欄顯示*/
			});
		});
          
	</script>
</body>
</html>