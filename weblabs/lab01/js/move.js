// 屏幕标号的负值（层数）
$('.ddw').val(0);
// 当前还能不能滑动, 0表示能
$('.ddw2').val(0);

/*
	setTimeout(function, time) 一段时间之后执行某函数
	stop() 函数，停止目前在指定元素上运行的所有动画
	animate() 函数，创建自定义动画
*/
setTimeout(function(){
	// 找到第一个num类的元素，找到其中的p标签，停止在上面运行的所有动画，执行自定义动画
	// 自定义动画：500ms 内，让指定的元素运动到距离顶端 50% 的地方
		$('.num').eq(0).find('.title').stop().animate({'top':'40%'},500) 
	// 250 毫秒后执行
	}, 250);

// 页面加载完毕之后执行
$(function(){
	$('.num_box').mousewheel(function(event, delta) {
		// canSlide 表示当前还能不能滑动
		var canSlide =$('.ddw2').val();
		console.log("canSlide = " + canSlide);
		if (canSlide == 1){
			return;	
		}
		// delta 表示鼠标滚轮方向， 1表示向上滚动，-1表示向下滚动
		doActive(delta);
	});
});

// 函数的参数：鼠标滚轮方向
// 1表示向上 -1表示向下
function doActive(a){
	// 从这里可以看出 ddw 是当前距离页面顶部的层数
	var nagtiveNumIndex =$('.ddw').val();
	// 当前距离页面顶部的层数，也就是屏幕标号的 负值
	b = parseInt(nagtiveNumIndex);

	// 屏的数量
	AllScreens = $('.num').length;
	if(a < 0){
		// 如果向下滚
		if(-b == AllScreens - 1){
			// 滚到底了，直接返回
			return;
		}
		// 没滚到底
		b -= 1;
		$('.ddw2').val(1);
	}else if(a > 0){
		// 如果向上滚
		if(-b == 0){
			// 滚到顶了
			return;
		}
		// 没滚到顶
		b += 1;
		$('.ddw2').val(1);
	}

	// 此时 b 已经变成了 -> 当前滑到了哪块屏幕上。 
	if(-b == 0){
		// 应该在首页屏幕
		$('.num').eq(1).find('div').animate({'top':'0'},500);
		setTimeout(function(){
			$('.num').eq(0).find('.title').animate({'top':'40%'},500);
		},1300);
	}else if(-b == 1){
		$('.num').eq(0).find('.title').animate({'top':'0'},500);
		$('.num').eq(2).find('div').animate({'top':'0'},500);
		setTimeout(function(){
			$('.num').eq(1).find('.personal-info').animate({'top':'10%'},500);
		},1300);

	}else if(-b == 2){
		$('.num').eq(1).find('div').animate({'top':'0'},500);
		setTimeout(function(){
			$('.num').eq(2).find('div').animate({'top':'10%'},500);
		},1300);

	}

	// 当前所在层数
	$('.ddw').val(b);
	// 屏幕高度
	var single_hh = $(window).height();
	// 当前应该在的屏幕高度 = 页面高度 * 层数
	click_hh =- single_hh * b;
	$('.num_box').animate({'bottom': click_hh}, 1000);
	setTimeout(function(){
		$('.ddw2').val(0);
	},1400);
}

// 调整屏幕大小（让他能全屏显示）
function formatScreenSize(){
	var single_hh = $(window).height();
	var single_ww = $(window).width();
	$('.num').height(single_hh);
	$('.num').width(single_ww);
}

formatScreenSize();

// 调整屏幕大小
$(window).resize(function(){
	if (typeof indexSlides != 'undefined' && indexSlides.reformat) 
		indexSlides.reformat();
	formatScreenSize();
});
