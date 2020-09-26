// 当表单发生提交行为的时候
$('#userForm').on('submit', function () {
	// 获取到用户在表单中输入的内容并将内容格式化成参数字符串
	var formData = $(this).serialize();
	// 向服务器端发送添加用户的请求
	$.ajax({
		type: 'post',
		url: '/users',
		data: formData,
		success: function () {
			// 刷新页面
			alert("添加成功");
			location.reload();
		},
		error: function () {
			alert('用户添加失败')
		}
	})
	// 阻止表单的默认提交行为
	return false;
});


// 当用户选择文件的时候
$('#modifyBox').on('change','#avatar',function(){
	// 用户选择到的文件
	// this.files[0]
	var formData = new FormData();
	formData.append('avatar', this.files[0]);

	$.ajax({
		type: 'post',
		url: '/upload',
		data: formData,
		// 告诉$.ajax方法不要解析请求参数
		processData: false,
		// 告诉$.ajax方法不要设置请求参数的类型
		contentType: false,
		success: function (response) {
			console.log(response)
			// 实现头像预览功能
			$('#preview').attr('src', response[0].avatar);
			$('#hiddenAvatar').val(response[0].avatar);
		}
	})
});


// 向服务器端发送请求 索要用户列表数据
$.ajax({
	type: 'get',
	url: '/users',
	success: function (response) {
		console.log(response)
		// 使用模板引擎将数据和HTML字符串进行拼接
		var html = template('userTpl', { data: response });
		// 将拼接好的字符串显示在页面中
		$('#userBox').html(html);
	}
});

// 通过事件委托的方式为编辑按钮添加点击事件
$('#userBox').on('click', '.edit', function () {
	// 获取被点击用户的id值
	var id = $(this).attr('data-id');
	// 根据id获取用户的详细信息
	$.ajax({
		type: 'get',
		url : '/users/' + id,
		success: function (response) {
			console.log(response)
			var htmls = template('modifyTpl', response);
			$('#modifyBox').html(htmls);
		}
	})
});

// 为修改表单添加表单提交事件
$('#modifyBox').on('submit', '#modifyForm', function () {
	// 获取用户在表单中输入的内容
	var formData = $(this).serialize();
	// 获取要修改的那个用户的id值
	var userid = $(this).attr('data-id');
	// 发送请求 修改用户信息
	$.ajax({
		type: 'put',
		url: '/users/' + userid,
		data: formData,
		success: function (response) {
			// 修改用户信息成功 重新加载页面
			location.reload()
		}
	})

	// 阻止表单默认提交
	return false;
});


//事件委托删除用户
$('#userBox').on('click','.delete',function(){
	if(confirm('您真的要删除该用户吗？'))
	{
		//确认删除用户

		//获取要删除用户的ID
		var id=$(this).attr('data-id');
		//alert(id);

		$.ajax({
		type: 'delete',
		url: '/users/' + id,
		success:function(){
			location.reload();
		}
		})
	}

}); 

//获取全选按钮
var selsectAll=$('#selsectAll');
var deleteMany=$('#deleteMany');

selsectAll.on('change',function(){
	//获取全选按钮当前状态
	var status=$(this).prop('checked');
	//alert(status);

	//获取批量删除按钮
	
	//批量删除显示
	if(status)
	{
		//显示批量删除按钮
		deleteMany.show();
	}
	else
	{
		//隐藏批量删除按钮
		deleteMany.hide();
	}


	//获取所有用户，同步用户状态和全选状态
	$('#userBox').find('input').prop('checked',status);

});

//事件委托把用户选中状态同步给全选框
$('#userBox').on('change','.userStatus',function(){
	//获取所有用户，在所有用户中过滤出选中的用户
	//判定选中用户的数量和所有用户的数量是否一致
	//如果一致，则说明所有用户都是被选中了
	//否则就是有的用户没被选中
	var AlluserCount=$('#userBox').find('input');
	if(AlluserCount.length==AlluserCount.filter(':checked').length)
	{
		//alert('所有用户都被选中');
		selsectAll.prop('checked',true);
	}
	else
	{
		//alert('非所有用户都被选中');
		selsectAll.prop('checked',false);
	}

	//如果选中的复选框的数量大于0，则有选中的复选框
	if(AlluserCount.filter(':checked').length>0)
	{
		//显示批量删除按钮
		deleteMany.show();
	}
	else
	{
		//隐藏批量删除按钮
		deleteMany.hide();
	}

});

//为批量删除添加点击事件
deleteMany.on('click',function(){
	var ids=[];
	//获取选中的用户
	var checkeduser= $('#userBox').find('input').filter(':checked');

	//循环复选框 从复选框元素的身上获取data-id的值
	checkeduser.each(function(index,element){
		ids.push($(element).attr('data-id'));
	});

	if(confirm('您真的要确定进行批量删除操作吗？'))
	{
		$.ajax({
			type:'delete',
			url:'/users/'+ids.join('-'),
			success:function(){
				location.reload();
			}

		})
	}
});
