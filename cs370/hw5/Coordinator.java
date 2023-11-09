import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;

class Coordinator {
	public static void main(String[] args) {
		/* 
		 * Your code goes in here
		 */
		int seed  =  Integer.parseInt(args[0]);
		int alphaseed = Integer.parseInt(args[1]);
		Random ran = new Random(seed);

		int buffsize = ran.nextInt(15-10+1)+10; // Number of Elements in buffer/buffer size
		int prod = ran.nextInt(40-20+1)+20; // Nunber of Items to be produced 
		// int cons = ran.nextInt(40-20+1)+20; // Number of Items to be consumed
        int ncons = ran.nextInt(7-3+1)+3; // Number of Consumers
		int ngen = ran.nextInt(7-3+1)+3; // Numbner of Generators
        Buffer buff = new Buffer(buffsize);
		int perGen = prod / ngen;
		int perCon = prod / ncons;
		int leftCon = prod % ncons;
		int leftGen = prod % ngen;
		System.out.println("[Coordinator] Buffer Size: "+ buffsize);
		System.out.println("[Coordinator] Total Items: "+ prod);
		System.out.println("[Coordinator] No. of Generators: "+ ngen);
		System.out.println("[Coordinator] No. of Consumers: "+ ncons);
		Generator[] genArray = new Generator[ngen];
		Consumer []conArray = new Consumer[ncons];

		for (int i = 0; i < ngen ; i++){
			if (i  == ngen + 1 ){
				Generator gen =  new Generator(buff, perGen+leftGen, i+1, alphaseed );
				genArray[i] = gen;
			}
			else{
				Generator gen =  new Generator(buff, perGen, i+1, alphaseed );
				genArray[i] = gen;
			}
		}
		for (int i = 0; i < ncons; i++){
			if (i  == ncons +1 ){
				Consumer consu =  new Consumer(buff, perCon+leftCon, i+1);
				conArray[i] = consu;
			}
			else{
				Consumer consu =  new Consumer(buff, perCon, i+1);
				conArray[i] = consu;
			}
		}
		int conC = 0;
		int conG = 0;
		for (int j = 0; j < ncons; j++){
			
			conArray[j].start();
		}
		for (int j = 0; j < ngen; j++){
			genArray[j].start();
		}
		try{
			for (int j = 0; j < ncons; j++){
			
				conArray[j].join();
			}
			for (int j = 0; j < ngen; j++){
				genArray[j].join();
			}
		}
		catch(Exception e){e.printStackTrace();}
		for (int k = 0; k < conArray.length; k++){
			conC = conC +conArray[k].getCConsonents();
		}
		for (int k = 0; k < genArray.length; k++){
			conG =  conG+ genArray[k].getGConsonents();
		}
		
		if (conC == conG){
			String s = String.format("The generated & consumed numbers of consonants are the same as shown: %d"+ conG);
			System.out.println(s);
		}
	}

	//Call this function from your generator or your consumer to get the time stamp to be displayed
	public static String getTime() {
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}