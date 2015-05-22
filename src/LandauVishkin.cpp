#include <lvlib/LandauVishkin.hpp>

integer match(const byte* str1,const byte* str2){
    integer count =0;
    while(str1[count] == str2[count]){
        count++;
    }
    return(count);
}

void landauVishkin_DC(Text* text_text,Text* pattern_text,integer errors, Text* output){
    byte* pattern;
    byte* text;
    integer pattern_length;
    integer text_length;
    integer prev, cur, next;
    integer base;
    integer i,j;
    integer* l_array;

    pattern_length = pattern_text->getLength();
    text_length = text_text->getLength();

    pattern = new byte[pattern_length+1];
    text = new byte[text_length+1];
    l_array = new integer[text_length+errors+2];

    text_text->readBuffer(text,0,text_length);
    pattern_text->readBuffer(pattern,0,pattern_length);
    text[text_length]= 0;
    pattern[pattern_length] = 1;

    //initialization
    for(i=0;i<text_length+errors+2;i++)
        l_array[i] = -2;

    /**Landau Vishkin algorithm**/
    base = errors;
    for(i=0;i<=errors;i++){
        //initialization
        prev = -2;
        cur = i-2;
        next = l_array[base-i+1];
        l_array[base+text_length] = -2;
        for(j=base-i;j<base+text_length;j++){
            if(cur+j-base >= text_length-1){
                l_array[j] = std::max(next+1,prev);
                l_array[j] = std::max(cur,l_array[j]);
            }
            else{
                l_array[j] = std::max(cur+1,prev);
                l_array[j] = std::max(l_array[j],next+1);
            }
            l_array[j] = std::min(l_array[j],pattern_length-1);
            l_array[j]+= match(text+l_array[j]+1+j-base,pattern+l_array[j]+1);
            prev = cur;
            cur = next;
            next = l_array[j+2];
        }
    }
#ifdef SHOW
    std::cout << "The pattern ends in text with at most " << errors << " errors " << "at positions:" << "\n";
    for(j=0;j<errors+text_length;j++){
        if(l_array[j]==pattern_length-1){
            std::cout << j-errors+l_array[j]  << "\n";
        }
    }
#endif
    /**Clean up**/
    delete[] pattern;
    delete[] text;
    delete[] l_array;
}

//Code by Ilie and Navarro
void landauVishkin_DC_Navarro(Text* text_text,Text* pattern_text,integer k, Text* output){
    int e,d,v1,v2,v3,i;
    int *L;
    byte* P;
    byte* T;
    integer m,n;

    m = pattern_text->getLength();
    n = text_text->getLength();

    P = new byte[m+1];
    T = new byte[n+1];

    //Initialization
    text_text->readBuffer(T,0,n);
    pattern_text->readBuffer(P,0,m);

    //End of string with special markers
    T[n]  = 0;
    P[m]= 1;

    L = new int[k+1+n+2];
    L += k+1;


       // e=0
#ifdef SHOW
    for (d=-k;d<-0;d++) printf ("   ");
#endif
       for (d=0;d<n;d++)
           { L[d] = match(P,T+d);
#ifdef SHOW
   printf ("%i  ",L[d]);
#endif
       }
#ifdef SHOW
    printf ("\n");
#endif
       L[n+1] = -1;
       // e>0
       for (e=1;e<=k;e++)
          { v1 = v2 = 0; v3 = L[-e+1];
          // invariant: v1 = L[d-1,e-1], v2 = L[d,e-1], v3 = L[d+1,e-1];
#ifdef SHOW
    for (d=-k;d<-e;d++) printf ("   ");
#endif
            for (d=-e;d<n;)
           { i = v1; if (v2 >= i) i = v2+1; if (v3 >= i) i = v3+1;
             L[d] = i + match(P+i,T+d+i);
#ifdef SHOW
    printf ("%i  ",L[d]);
 #endif
             v1 = v2; v2 = v3; v3 = L[++d+1];
           }
#ifdef SHOW
    printf ("\n");
#endif
       }
       // e=k, reporting
          { v1 = v2 = 0; v3 = L[-e+1];
          // invariant: v1 = L[d-1,e-1], v2 = L[d,e-1], v3 = L[d+1,e-1];
#ifdef SHOW
    for (d=-k;d<-e;d++) printf ("   ");
#endif
            for (d=-e;d<n;)
           { i = v1; if (v2 >= i) i = v2+1; if (v3 >= i) i = v3+1;
             L[d] = i + match(P+i,T+d+i);
#ifdef SHOW
             if (L[d] >= m-1)
            { printf ("Match at %i\n",d+m); }
#endif
#ifdef SHOW
   printf ("%i  ",L[d]);
#endif
             v1 = v2; v2 = v3; v3 = L[++d+1];
           }
   #ifdef SHOW
   printf ("\n");

   #endif
       }

        P[m] = 0;
        delete[] ((int*)L-k-1);
        delete[] P;
        delete[] T;
}

void landauVishkin_DC_Parallel_ProcessDiagonals(const LV_DC_parallel_struct_t& LV_struct){
    integer* l_array;
    integer base;
    integer prev;
    integer cur;
    integer next;
    integer last;
    integer begin;
    integer end;
    byte* pattern;
    byte* text;
    integer text_length;
    integer pattern_length;
    integer j;

    //Initialization
    l_array = LV_struct.l_array;
    base =  LV_struct.base;
    prev =  LV_struct.prev;
    cur =  LV_struct.cur;
    next =  LV_struct.next;
    begin =  LV_struct.begin;
    end = LV_struct.end;
    pattern =  LV_struct.pattern;
    text =  LV_struct.text;
    text_length = LV_struct.text_length;
    pattern_length = LV_struct.pattern_length;
    last = LV_struct.last;
    //End of initialization

    //parallel step
    //TODO: RESOLVE BRANCH DEPENDENCIES
    for(j=begin;j<end-1;j++){
       if(cur+j-base >= text_length-1){
            l_array[j] = std::max(next+1,prev);
            l_array[j] = std::max(cur,l_array[j]);
        }
        else{
            l_array[j] = std::max(cur+1,prev);
            l_array[j] = std::max(l_array[j],next+1);
        }

        l_array[j] = std::min(l_array[j],pattern_length-1);
        l_array[j]+= match(text+l_array[j]+1+j-base,pattern+l_array[j]+1);
        prev = cur;
        cur = next;
        next = l_array[j+2];
    }
    next = last;
    l_array[j] = std::max(cur+1,prev);
    l_array[j] = std::max(l_array[j],next+1);
    l_array[j] = std::min(l_array[j],pattern_length-1);
    l_array[j]+= match(text+l_array[j]+1+j-base,pattern+l_array[j]+1);

}

void landauVishkin_DC_Parallel(Text* text_text,Text* pattern_text,
                               integer errors, Text* output){
    byte* pattern;
    byte* text;
    integer pattern_length;
    integer text_length;
    integer base;
    integer i,j;
    integer* l_array;
    std::thread* threads;
    LV_DC_parallel_struct_t* LV_structs;
    integer thread_block_size;

    pattern_length = pattern_text->getLength();
    text_length = text_text->getLength();

    pattern = new byte[pattern_length+1];
    text = new byte[text_length+1];
    l_array = new integer[text_length+errors+3];

    //Initialization
    text_text->readBuffer(text,0,text_length);
    pattern_text->readBuffer(pattern,0,pattern_length);

    //End of string with special markers
    text[text_length]  = 0;
    pattern[pattern_length]= 1;

    threads = new std::thread[LV_NUMBER_OF_THREADS];
    LV_structs = new LV_DC_parallel_struct_t[LV_NUMBER_OF_THREADS];
    //initialization
    for(i=0;i<text_length+errors+3;i++)
        l_array[i] = -2;

    /**Landau Vishkin algorithm**/

    base = errors+1;
    for(i=0;i<=errors;i++){
        // Parallel step, give a block of diagonals to each thread
        thread_block_size = std::max(1,(i+text_length)/LV_NUMBER_OF_THREADS);
        for(j=0;j<LV_NUMBER_OF_THREADS;j++){
            //Initialize threads attributes
            LV_structs[j].l_array = l_array;
            LV_structs[j].base = base;
            LV_structs[j].prev = l_array[base+j*thread_block_size-i-1];
            LV_structs[j].cur =  j == 0  ?  i-2 : l_array[base+j*thread_block_size-i];
            LV_structs[j].next = l_array[std::min(base+j*thread_block_size-i+1,base+text_length)];
            LV_structs[j].begin = base+j*thread_block_size-i;
            LV_structs[j].end = j == LV_NUMBER_OF_THREADS-1 ? base+text_length : LV_structs[j].begin + thread_block_size;
            LV_structs[j].last = l_array[LV_structs[j].end];
            LV_structs[j].pattern = pattern;
            LV_structs[j].text = text;
            LV_structs[j].text_length = text_length;
            LV_structs[j].pattern_length = pattern_length;
        }
        //Run Threads
        for(j=0;j<LV_NUMBER_OF_THREADS;j++){
           threads[j] = std::thread(landauVishkin_DC_Parallel_ProcessDiagonals,LV_structs[j]);
        }
        //Join Threads
        for(j=0; j< LV_NUMBER_OF_THREADS;j++){
            threads[j].join();
        }
    }
#ifdef SHOW
    std::cout << "The pattern ends in text with at most " << errors << " errors " << "at positions:" << "\n";
    for(j=0;j<errors+text_length;j++){
        if(l_array[j]==pattern_length-1){
            std::cout << j-errors+l_array[j]-1  << "\n";
        }
    }
#endif
    /**Clean up**/
    delete[] pattern;
    delete[] text;
    delete[] l_array;
    delete[] LV_structs;
}



void landauVishkin_DC_Semi_External(Text* text_text,Text* pattern_text,integer errors, Text* output){
    byte* pattern;
    byte* text;
    int fd;
    integer pattern_length;
    integer text_length;
    integer row;
    integer in,out;
    integer i,j,x,y;
    integer count;
    integer l_array_size;
    char tmp_name_input[] = "/media/SSD/fileXXXXXX" ;
    char tmp_name_output[] = "/media/SSD/fileXXXXXX";
    integer* l_array_input;
    integer* l_array_output;
    integer next_read;

    std::fstream temp_file[2]; /**@var File which stores the read/written values in external memory**/

    pattern_length = pattern_text->getLength();
    text_length = text_text->getLength();

    pattern = new byte[pattern_length+1];
    text = new byte[text_length+1];


    text_text->readBuffer(text,0,text_length);
    pattern_text->readBuffer(pattern,0,pattern_length);
    pattern[pattern_length] = 0;
    text[text_length] = 1;

    //Allocate memory for the auxiliar arrays
    l_array_input = new integer[LV_BLOCK_SIZE];
    l_array_output = new integer[LV_BLOCK_SIZE];

    fd = mkstemp(tmp_name_input);
    if( fd ==-1){
        perror("Mkstemp error: ");
        std::exit(EXIT_FAILURE);
    }
    close(fd);
    fd = mkstemp(tmp_name_output);

    if(fd ==-1){
        perror("Mkstemp error: ");
        std::exit(EXIT_FAILURE);
    }
    close(fd);

    try{
        temp_file[0].open(tmp_name_input,std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
        temp_file[1].open(tmp_name_output,std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
    }
    catch(std::fstream::failure e){
        std::cout << e.what();
    }

    //initialization
    l_array_size = text_length+errors+2;
    row = -2;
    for(i=0;i<l_array_size;i++)
        temp_file[0].write(reinterpret_cast<const char*> (&row), sizeof(row));

    /**LV algorithm**/
    for(i=0;i<=errors;i++){

        temp_file[i%2].clear();
        temp_file[i%2].seekg(0,std::ios_base::beg);
        temp_file[i%2].seekp(0,std::ios_base::beg);
        temp_file[(i+1)%2].clear();
        temp_file[(i+1)%2].seekg(0,std::ios_base::beg);
        temp_file[(i+1)%2].seekp(0,std::ios_base::beg);

        //initialization
        next_read = -2;
        l_array_input[1] = i-2;
        l_array_input[0] = -2;
        j=0;
        do{
            //read results
            //input[0] = -2   input[1] i-2  input[|text|] = -2
            temp_file[i%2].read(reinterpret_cast<char*> (l_array_input+2), LV_BLOCK_SIZE*sizeof(word) - 2*sizeof(word));
            next_read = std::min(LV_BLOCK_SIZE-2,i+text_length - j);
            if(i+text_length-j <=LV_BLOCK_SIZE-2){
                l_array_input[next_read+1] = -2;
            }

            //For every digagonal within a block
            for(in=1,out=0;in<=next_read;j++,in++,out++){
                if(l_array_input[in]+j-i >= text_length-1){
                    l_array_output[out] = std::max(l_array_input[in+1]+1,l_array_input[in-1]);
                    l_array_output[out] = std::max(l_array_input[out],l_array_input[in]);
                }
                else{
                    l_array_output[out] = std::max(l_array_input[in]+1,l_array_input[in-1]);
                    l_array_output[out] = std::max( l_array_output[out],l_array_input[in+1]+1);
                }

                l_array_output[out] = std::min(pattern_length-1,l_array_output[out]);

                for(count=0,y=l_array_output[out]+1,x = y+j-i; (text[x]==pattern[y]) && (x < text_length) && (y<pattern_length);x++,y++)
                    count++;
                l_array_output[out]+= count;
            }
            //write results
            temp_file[(i+1)%2].write(reinterpret_cast<char*> (l_array_output), (out)*sizeof(word));
            l_array_input[0] = l_array_input[in-1];
            l_array_input[1] = l_array_input[in];

        }while(j< i + text_length);
    }
    temp_file[i%2].clear();
    temp_file[i%2].seekg(0,std::ios_base::beg);
    temp_file[i%2].seekp(0,std::ios_base::beg);
    //Display Results
#ifdef SHOW
    std::cout << "The pattern ends in text with at most " << errors << " errors " << "at positions:" << "\n";
    for(j=0;j<errors+text_length;j++){
        temp_file[i%2].read(reinterpret_cast<char*> (&row),sizeof(word));
        if(row==pattern_length-1){
            std::cout << j-errors+row  << "\n";
        }
    }
#endif
    /**Clean up**/
    delete[] pattern;
    delete[] text;
    delete[] l_array_input;
    delete[] l_array_output;
    temp_file[0].close();
    temp_file[1].close();
    if(remove(tmp_name_input)!=0)
        std::cerr << "Error deleting file " << tmp_name_input << "\n";
    if(remove(tmp_name_output)!=0)
        std::cerr << "Error deleting file " << tmp_name_output << "\n";
}
