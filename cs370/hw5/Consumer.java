import java.util.Random;

public class Consumer extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;
    Buffer Buff;
	int numCConso = 0;
	int count, id;


	public Consumer(Buffer buff, int count, int id) {
		//Assign values to the variables
		this.Buff = buff;
		this.count = count;
		this.id = id;
	}

	@Override
	public void run() {
		/* Your code goes in here

		Insert the N-th prime to the buffer as much as the count.
        The random number N is produced by random generator. Check the range in the HW description.
        You can generate a random number in range [1, 10] as:
        int randomN = randomWithSeed.nextInt(10-1+1) + 1;

		*/
		int count = this.count;
		int id = this.id;

        while (count != 0){

            int index = Buff.out;
			char ans = Buff.remove();
			if (ans != 'A' && ans != 'E' && ans != 'I' && ans != 'O' && ans != 'U'){
				numCConso = numCConso + 1;
			}
			if (ans != 0){
				String s = String.format("[Consumer %d]: consumed %s at index %d at time %s",id, ans, index, Coordinator.getTime());
				System.out.println(s);
				count--;
			}
			
			
        }
	}
	public int getCConsonents(){
		return numCConso;
	}
}
