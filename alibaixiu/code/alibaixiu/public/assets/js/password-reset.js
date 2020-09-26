//当修改密码表单发生提交行为
$('#modifyForm').on('submit',function(){
	//获取用户表单输入内容
	var formData= $(this).serialize();
	//调用接口实现密码修改
	console.log(formData)
	$.ajax({
		url:'/users/password',
		type:'put',
		data:formData,
		success:function(){
			location.href= "/admin/login.html"
		}
	})
	//阻止自动提交
	return false;
});