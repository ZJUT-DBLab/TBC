#include <iostream>
#include <chrono>
#include "Transformer.h"
#include "Computer.h"
using namespace std;
using namespace chrono;
struct Settings
{
	bool isStrict = true;
	bool needCompress = false;
	bool runshortest = false;
	bool runshortestforemost = false;

};
auto time_cost = [](const auto st, const auto en) {
	return ((double)duration_cast<microseconds>(en - st).count()) * microseconds::period::num / microseconds::period::den;
};

int main()
{
	Settings setting;
	vector<string> filenames;
	//filenames.push_back("../data-set/highschool2011.txt");
	/*filenames.push_back("../data-set/highschool2012.txt");
	filenames.push_back("../data-set/highschool2013.txt");
	filenames.push_back("../data-set/hospital-award.txt");
	filenames.push_back("../data-set/hypertext.txt");
	filenames.push_back("../data-set/infectious.txt");
	filenames.push_back("../data-set/primaryschool.txt");
	 filenames.push_back("../data-set/edit-itwikivoyage.txt");
	filenames.push_back("../data-set/radoslaw_email_email.txt");
	filenames.push_back("../data-set/edit-sewiki.txt");
	filenames.push_back("../data-set/sx-mathoverflow.txt");
	filenames.push_back("../data-set/superuser.txt");*/
	/*filenames.push_back("../data-set/1_edit-tgwiktionary_u_i_ts.txt");
	filenames.push_back("../data-set/2_edit-mlwikiquote_u_i_ts.txt");
	filenames.push_back("../data-set/3_edit-mgwikipedia_u_i_ts.txt");
	filenames.push_back("../data-set/4_edit-plwikiquote_u_i_ts.txt");
	filenames.push_back("../data-set/5_edit-ltwiktionary_u_i_ts.txt");
	filenames.push_back("../data-set/6_edit-zhwiktionary_u_i_ts.txt");
	filenames.push_back("../data-set/7_edit-warwikipedia_u_i_ts.txt");
	filenames.push_back("../data-set/8_edit-mgwiktionary_u_i_ts.txt");*/
	for (int i = 0; i < filenames.size(); i++)
	{
		Transformer transformer = Transformer(filenames[i]);
		auto begin = chrono::system_clock::now();
		transformer.doTransform(setting.isStrict);
		cout << "transforming completed" << endl;
		auto transform_time = chrono::system_clock::now();
		cout << "transform_time:" << time_cost(begin, transform_time) << endl;
		if (setting.needCompress)
		{
			transformer.doCompress();
			auto compress_time = chrono::system_clock::now();
			cout << "compressing completed" << endl;
			cout << "compress_time:" << time_cost(transform_time, compress_time) << "second" << endl;
			Computer cpu = Computer(transformer);
			//if (setting.runfastest)
			//{
			//	/*cpu.computeByFastestPath();
			//	auto finish = chrono::system_clock::now();
			//	cout << "compute_time:" << time_cost(compress_time, finish) << "second" << endl;
			//	cout << "node compress ratio:" << 1 - (double)cpu.transformer.cmp_graph.cmp_data_nodes.size() / cpu.transformer.tran_nodes.size() << endl;
			//	cout << "edge compress ratio:" << 1 - (double)cpu.transformer.cmp_edge_size / cpu.transformer.tran_edge_size << endl;
			//	vector<double>& BC = cpu.BC;*/
			//	//bucket(BC);
			//	/*for (int i = 0; i < BC.size(); i++)
			//	{
			//		cout << "seq: " << i << "\t" << BC[i] << endl;
			//	}*/
			//}
			//if (setting.runforemost)
			//{
			//	cpu.computeByForemostPath();
			//	auto finish = chrono::system_clock::now();
			//	cout << "compute_time:" << time_cost(compress_time, finish) << "second" << endl;
			//	cout << "node compress ratio:" << 1 - (double)cpu.transformer.cmp_graph.cmp_data_nodes.size() / cpu.transformer.tran_nodes.size() << endl;
			//	cout << "edge compress ratio:" << 1 - (double)cpu.transformer.cmp_edge_size / cpu.transformer.tran_edge_size << endl;
			//	vector<double>& BC = cpu.BC;
			//	/*for (int i = 0; i < BC.size(); i++)
			//	{
			//		cout << "seq: " << i << "\t" << BC[i] << endl;
			//	}*/
			//	//bucket(BC);
			//}
			if (setting.runshortestforemost)
			{
				cpu.computeByShortestForemostPath();
				auto finish = chrono::system_clock::now();
				cout << "compute_time:" << time_cost(compress_time, finish) << "second" << endl;
				vector<double>& BC = cpu.BC;
				/*for (int i = 0; i < BC.size(); i++)
				{
					cout << "seq: " << i << "\t" << BC[i] << endl;
				}*/
				
			}
			if (setting.runshortest)
			{
				cpu.computeByShortestPath();
				auto finish = chrono::system_clock::now();
				cout << "compute_time:" << time_cost(compress_time, finish) << "second" << endl;
				vector<double>& BC = cpu.BC;
				/*for (int i = 0; i < BC.size(); i++)
				{
					cout << "seq: " << i << "\t" << BC[i] << endl;
				}*/
				
			}
		}
		else
		{
			Computer cpu = Computer(transformer);
			
			if (setting.runshortestforemost)
			{
				cpu.computeByShortestForemostPathT();
				auto finish = chrono::system_clock::now();
				cout << "compute_time:" << time_cost(transform_time, finish) << "second" << endl;
				vector<double>& BC = cpu.BC;
				/*for (int i = 0; i < BC.size(); i++)
				{
					cout << "seq: " << i << "\t" << BC[i] << endl;
				}*/
			
			}
			if (setting.runshortest)
			{
				cpu.computeByShortestPathT();
				auto finish = chrono::system_clock::now();
				cout << "compute_time:" << time_cost(transform_time, finish) << "second" << endl;
				vector<double>& BC = cpu.BC;
				for (int i = 0; i < BC.size(); i++)
				{
					cout << transformer.seq_to_identity[i] << " " << BC[i] << endl;
				}
				/*for (int i = 0; i < BC.size(); i++)
				{
					cout << "seq: " << i << "\t" << BC[i] << endl;
				}*/
			
			}
			
		}
	}
}
