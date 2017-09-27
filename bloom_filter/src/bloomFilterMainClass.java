import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
/*This Class provide User Interface */
public class bloomFilterMainClass {
	public static bloomFilter make_new_bloomfilter(int filter_size_log2,int numhash){
		
		return new bloomFilter.bloomBuilder().set_num_hashes(numhash).set_bloom_table_size(filter_size_log2) .build();
	}
	public static void main(String[] args)throws IOException {
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		int filter_size;
		int hash;
		int op;
		bloomFilter bf;
		System.out.println("Note:size of Bloom filter = 2^size");
		System.out.println("Enter size of BLOOM FILTER\t");
		filter_size=Integer.parseInt(br.readLine());
		System.out.println("Enter number of hashes\t");
		hash=Integer.parseInt(br.readLine());
		bf=make_new_bloomfilter(filter_size,hash);	
		
		do{
			System.out.println("\nPress\n1:Add url\n2:Search url\n3:Reset\n4:EXIT");
			op=Integer.parseInt(br.readLine());
			
			if(op==1){
				System.out.println("Enter url:");
				String url=br.readLine();
				bf.insert(url);
			}
			else if(op==2){
				System.out.println("Enter url:");
				String url=br.readLine();
				if(bf.isPresent(url))System.out.println("\nUrl MAY BE blacklisted");
				else System.out.println("\nUrl was NOT blacklisted");
			}
			else if(op==3)
			{
				System.out.println("Note:size of Bloom filter = 2^size");
				System.out.println("Enter size of BLOOM FILTER(2^size)\t");
				filter_size=Integer.parseInt(br.readLine());
				System.out.println("Enter number of Hashes\t");
				hash=Integer.parseInt(br.readLine());
				bf=make_new_bloomfilter(filter_size,hash);	
			}
			
			
			
			
		}while(op!=4);
		
		
		System.out.println();
		System.out.println();
		System.out.println();
	}

	}


