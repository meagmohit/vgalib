/*
 *  Designed By:-
 *  Mohit Agarwal 
 *  Electronics Club, IIT Kanpur
 *  Contact: mohita@iitk.ac.in
 *  See Project Documentation for more details
*/
void rect(int a1,int b1,int a2,int b2,int c)
{
     int x;
     int y;
    y=b1;
    for (x=a1;x<=a2;x++)
    {
                   SRAM_Write(x,y,c);
                   SRAM_Write(x,y+b2-b1,c);
    }
    x=a1;
    for (y=b1;y<=b2;y++)
    {
                   SRAM_Write(x,y,c);
                   SRAM_Write(x+a2-a1,y,c);
    }

}
