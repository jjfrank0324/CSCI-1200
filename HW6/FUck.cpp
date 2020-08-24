bool equal_board(vector<vector<string> >  a, vector<vector<string> >  b)
{
  for(unsigned int i =0; i< a.size(); i++)
    {
      for(unsigned int j =0; j < a[0].size();j++)
        {
          if(a[i][j] != b[i][j])
            return false;
        }
    }
    return true;
}

void erase_duplicate(vector<vector<vector<string> > > &solutions,vector<vector<string> > &all_sol)
{
  for(unsigned int i =0; i< solutions.size()-1; i++)
  {
    for(unsigned int j =i; j< solutions.size(); j++)
    {
      if(equal_board(solutions[i],solutions[j])==1)
        {
          cout<<"they are equal_board"<<endl;

          solutions.erase(solutions.begin()+i);
          i-=1;

        }
      // for(unsigned int m =0; m< solutions[0].size(); m++)
      // {
      //   for(unsigned int n =0; n< solutions[0][0].size(); n++)
      //   {
      //     if(solutions[i][m][n]!=solutions[j][m][n])
      //       {
      //         judge = false;
      //         cout<<"This case the differese "<< solutions[i][m][n]<<":"<<solutions[j][m][n];
      //
      //         m=solutions[0].size();
      //         n= solutions[0][0].size();
      //         j= solutions.size();
      //       }
      //       //j=solutions.size();
      //   }
      //
      // }
      // // if(judge == false)
      // // { //cout<<"BIIIIIIIIIIIIIIIII erasing!"<<endl;
      // //   solutions.erase(solutions.begin()+i);
      // //   all_sol.erase(all_sol.begin()+i);
      // //   i-=1;
      // //   break;
      // // //  cout<<"SUCCESSFULLY errase! "<<endl;
      // // }
      }
    // if(judge == true)
    // { //cout<<"BIIIIIIIIIIIIIIIII erasing!"<<endl;
    //   solutions.erase(solutions.begin()+i);
    //   all_sol.erase(all_sol.begin()+i);
    //   i-=1;
    // //  cout<<"SUCCESSFULLY errase! "<<endl;
    // }
  }
}
