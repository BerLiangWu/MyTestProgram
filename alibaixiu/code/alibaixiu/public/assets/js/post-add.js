//向服务器请求获取文章分类数据
$.ajax({
	type:'get',
	url:'/categories',
	success:function(response){
		console.log(response);
		var html=template('categoryTpl',{data:response});
		//console.log(html);
		$('#category').html(html);
}

});

//获取文件选择控件，添加选择事件
$('#feature').on('change',function(){
		//获取管理员选择的文件
		var file=this.files[0];
		//创建formData对象  实现二进制文件上传
		var formData= new FormData();
		formData.append('cover',file);
		//实现文章封面上传
		$.ajax({
			type:'post',
			url:'/upload',
			data:formData,
			//不处理data属性参数
			processData:false,
			//不设置参数类型
			contentType:false,
			success:function(response){
				console.log(response);
				$('#thumbnall').val(response[0].cover);
			}
		})
});


//当添加文章表达提交时
$("#addForm").on('submit',function(){
	//获取管理员输入内容
	var formData=$(this).serialize();
	//console.log(formData);
	//向服务器发送请求，添加文章
	$.ajax({
		type:'post',
		url:'/posts',
		data:formData,
		success:function(){
			//添加成功跳转到文章列表页面
			location.href='/admin/posts.html';

		}
	})
	//阻止默认提交
	return false;
});

//获取浏览器地址中的id
var id=getUrlParams('id');

//当前为修改文章操作
if(id!=-1)
{	
	//根据id获取文章信息
	$.ajax({
		type:'get',
		url:'/posts/'+id,
		success:function(response)
	{
		$.ajax({
		type:'get',
		url:'/categories',
		success:function(categories){
			//$('#createdControl').hide();
			response.categories = categories;
			console.log(response);
			var html=template('modifyTpl',response);
			console.log(html);
			$('#parentBox').html(html);
		}

		});
		
	}
	
	})

}



//从浏览器地址栏获取查询参数
function getUrlParams(name){
	//分割特殊符号
	var paramsAry=location.search.substr(1).split('&');
	for(var i=0;i<paramsAry.length;i++)
	{	
		//循环数据
		var tmp=paramsAry[i].split('=');
		if(tmp[0]==name){
			return tmp[1]
		}
	}
	return -1;
}


//处理日期
function formateDate(date){
	//讲日期时间字符串转换成日期对象
	date =new Date(date);
	return date.getFullYear()+'-'+(date.getMonth()+1)+'-'+date.getDate()+'T'+date.getHours()+':'+date.getMinutes();

}

//当修改文章信息表单发生提交行为
$('#parentBox').on('submit','#modifyForm',function(){
	//获取管理员表单输入内容
	var formData=$(this).serialize();
	//获取管理员修改的文章ID值
	var id= $(this).attr('data-id');
	//向服务器发送内容
	$.ajax({
		type:'put',
		url:'/posts/'+id,
		data:formData,
		success:function(){
			location.href='/admin/posts.html';
		}
	})
	//阻止默认提交
	return false;
});


