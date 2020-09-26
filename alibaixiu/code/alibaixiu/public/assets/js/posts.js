// 向服务器端发送请求 获取文章列表数据
$.ajax({
	type: 'get',
	url: '/posts',
	success: function (response) {
		//console.log(response);
		var html = template('postsTpl', response);
		//console.log(html);
		$('#postsBox').html(html);
		var page=template('pageTpl',response);
		$('#page').html(page);
	}
});


//处理日期
function formateDate(date){
	//讲日期时间字符串转换成日期对象
	date =new Date(date);
	return date.getFullYear()+'-'+(date.getMonth()+1)+'-'+date.getDate();
}

//分页代码
function changePage(page){
	//alert(page);
	//向服务器发送请求 获取分页列表
	$.ajax({
	type: 'get',
	url: '/posts',
	data:{
		page:page
	},
	success: function (response) {
		//console.log(response);
		var html = template('postsTpl', response);
		//console.log(html);
		$('#postsBox').html(html);
		var page=template('pageTpl',response);
		$('#page').html(page);
	}
});
}

//向服务器端发送请求索要分类数据
$.ajax({
	type: 'get',
	url: '/categories',
	success: function (response) {
		//console.log(response);
		var html=template('categoryTpl',{data:response});
		//console.log(html);
		$('#categoryBox').html(html);
	}
});



//获取筛选表单
$('#filterForm').on('submit',function(){
	//获取管理员选择的过滤条件
	var formData=$(this).serialize();
	console.log(formData);
	// 向服务器端发送请求 获取文章列表数据
$.ajax({
	type: 'get',
	url: '/posts',
	data: formData,
	success: function (response) {
		//console.log(response);
		var html = template('postsTpl', response);
		//console.log(html);
		$('#postsBox').html(html);
		var page=template('pageTpl',response);
		$('#page').html(page);
	}
});
	//阻止默认提交
	return false;
});


//删除文章事件
$('#postsBox').on('click','.delete',function(){
	
	if(confirm('您真的要删除吗？'))
	{	
		//获取要删除的ID,
		var id=$(this).attr('data-id');
		$.ajax({
			type:'DELETE',
			url:'/posts/'+id,
			success:function(){
				location.reload();
			}

		})
	}

});