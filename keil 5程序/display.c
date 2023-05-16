void display()
{
	goto_xy(1,0); 
	display_string("time ");
	goto_xy(1,6);
	display_num(hour);
	goto_xy(1,8);
	display_string(":");
	goto_xy(1,9);
	display_num(min);
	goto_xy(1,11);
	display_string(":");	
    goto_xy(1,12);
	display_num(sec);
//	goto_xy(2,0);
//		display_num1(infrard);
	goto_xy(2,5);
	display_num1(intensity);
	
}
