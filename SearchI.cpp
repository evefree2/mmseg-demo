/*
 * Search Server 
 * Created by edgar
 * Date:2012-08-16
 * Using for chinese seg and search sug
 *
 * */
#include "SearchI.h"

//load config file.
//init global env
//this is tmp,you can rewrite it.
void LoadConfig()
{

}
//init all function
void init()
{
	LoadConfig();
}
int main(int argc,char** argv)
{
	init();	//init gloabl function
		
	cmmseg mommseg;

	int lRet=mommseg.init_mmseg_libpath("/usr/local/mmseg/etc/");
	if(lRet !=0){
		cerr<<"cmmseg::init_mmseg_libpath error.lRet:"<<lRet<<endl;
		return -1;
	}
	lRet=mommseg.loadsegmenter();
	if(lRet !=0){
		cerr<<"loadsegmenter error."<<endl;
		return -1;
	}
	//sug seg
	string needwords="我们都是中国人，我们要好好学习，我们是社会注意的新一代。现在社会找工作好难呀，所以我们要努力。我们期待我们版本发布更规范，我们的产品越来越好!QQ2012,QQ音乐";
	int length=(int)needwords.length();
	mommseg.getallseg(needwords.c_str(),length);
	cout<<endl<<endl;
	//
	return 0;
}
