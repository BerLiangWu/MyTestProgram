//产生添加表单分类
$('#addCategory').on('submit',function(){
	
	var formData=$(this).serialize();
	//向服务器申请添加分类
	//alert('test');
	//console.log(formData)
	$.ajax({
		type:'post',
		url:'/categories',
		data: formData,
		success: function (){
			location.reload();
		}
	})
	//组织表单默认提交
	return false;
});
//发送请求展示分类
$.ajax({
	type:'get',
	url:'/categories',
	success:function(response){
		console.log(response);
		var html=template('categoryListTpl',{data:response});
		console.log(html);
		$('#categoryBox').html(html);
}

});

//为编辑按年添加点击案件
$('#categoryBox').on('click','.edit',function(){
	//获取要修改得分类数据id
	var id=$(this).attr('data-id');
	//根据ID获取分类数据信息
	$.ajax({
		type:'get',
		url:'/categories/'+id,
		success:function(response){
			console.log(response);
		}



	})
})

//为删除按钮添加点击事件
$('#categoryBox').on('click','.delete',function(){
	if(confirm('您真的要删除此分类吗？'))
	{
		//获取要删除的分类ID
		var id=$(this).attr('data-id');

		$.ajax({
			type:'delete',
			url:'/categories/'+id,
			success:function(){
				location.reload();
			}
		})
	}
});