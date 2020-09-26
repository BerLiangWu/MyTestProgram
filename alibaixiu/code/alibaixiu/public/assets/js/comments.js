//向服务器端发送请求，获取评论列表
$.ajax({
	type:'get',
	url:'/comments',
	success:function(response){
		console.log(response);
		var html=template('commentsTpl',response);
		//console.log(html);
		$('#commentsBox').html(html);
		var pagehtml=template('pageTpl',response);
		$('#pageBox').html(pagehtml);
	}
});


function changePage(page){
$.ajax({
	type:'get',
	url:'/comments',
	data:{
		page:page
	}
	success:function(response){
		console.log(response);
		var html=template('commentsTpl',response);
		//console.log(html);
		$('#commentsBox').html(html);
		var pagehtml=template('pageTpl',response);
		$('#pageBox').html(pagehtml);
	}
});


}



function formateDate(date){
	//讲日期时间字符串转换成日期对象
	date =new Date(date);
	return date.getFullYear()+'-'+(date.getMonth()+1)+'-'+date.getDate()+'T'+date.getHours()+':'+date.getMinutes();

}