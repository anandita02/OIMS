import java.util.BitSet;
/*This class  implements bloom filter*/
public class bloomFilter{

	private final BitSet bloom_table;
	private final int num_hashes;
	private final int hashMask;
	
	private final int bloom_table_size_log2;
	private long[] byteTable;
	private static final int MAX_HASHES = 8;
	private static final long HSTART = 0xBB40E64DA205B064L;
	private static long HMULT = 7664345821815920749L;
	long[] make_byteTable(){
	    
		long[] byteTable = new long[256 * MAX_HASHES];
	    long h = 0x544B2FBACAAF1684L;
	    for (int i = 0; i < byteTable.length; i++) {
	      for (int j = 0; j < 31; j++)
	        h = (h >>> 7) ^ h; h = (h << 11) ^ h; h = (h >>> 10) ^ h;
	      byteTable[i] = h;
	    }
	    return byteTable;
	  }
	private long hashCode(String s, int hcNo) {
	    long h = HSTART;
	    final long hmult = HMULT;
	    final long[] ht = this.byteTable;
	    int startIx = 256 * hcNo;
	    for (int len = s.length(), i = 0; i < len; i++) {
	      char ch = s.charAt(i);
	      h = (h * hmult) ^ ht[startIx + (ch & 0xff)];
	      h = (h * hmult) ^ ht[startIx + ((ch >>> 8) & 0xff)];
	    }
	    return h;
	  }
	bloomFilter(bloomBuilder obj)
	{
		
		
		this.num_hashes=obj.num_hashes;
		this.bloom_table_size_log2=obj.bloom_table_size_log2;
		this.hashMask=(1<<bloom_table_size_log2)-1;
		this.byteTable=this.make_byteTable();//stores random 64 bit numbers (used in hashing)
		this.bloom_table=new BitSet(1<<bloom_table_size_log2);
	}
	public void insert(String url)
	{  
		int hash_code_num,bit_num;
		
		
		for(hash_code_num=0;hash_code_num<num_hashes;hash_code_num++)
		{
		bit_num=(int) (hashMask & hashCode(url,hash_code_num));
		bloom_table.set(bit_num);
		}
	}
	public boolean isPresent(String url)
	{
		int hash_code_num,bit_num;
		
		for(hash_code_num=0;hash_code_num<num_hashes;hash_code_num++)
		{
			bit_num=(int) (hashMask & hashCode(url,hash_code_num));
		
			if(!bloom_table.get(bit_num)) return false;
			
		}
		return true;
		
	}
	public int get_num_hashes()
	{
		return this.num_hashes;
	}
	
	public static class bloomBuilder
	{
	
		
		private int num_hashes;
		
		private int bloom_table_size_log2;
		
	bloomBuilder(){
	}
		
	
	public bloomBuilder set_num_hashes(int num_hashes)
	{
		this.num_hashes=num_hashes;
		return this;
	}
	public bloomBuilder set_bloom_table_size(int num)
	{
		this.bloom_table_size_log2=num;
		return this;
	}
	public bloomFilter build()
	{   
		bloomFilter bf= new bloomFilter(this);
		if (bf.get_num_hashes() > MAX_HASHES ) {
		    throw new IllegalStateException("Not valid\n");
		    
		  }
		
		  return bf;
	}
	

}
}