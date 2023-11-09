import java.util.Random;

public class Generator extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;
    Buffer Buff;
	int numGConso = 0;
	int count, id, alphabetSeed;

	public Generator(Buffer buff, int count, int id, int alphabetSeed) {
		//Assign values to the variables
		this.Buff = buff;
		this.count = count;
		this.id = id;
		this.alphabetSeed = alphabetSeed;
		randomWithSeed = new Random(alphabetSeed);
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
			int index = Buff.in;
			char ans = (char) ('A'+  randomWithSeed.nextInt(26));
            Buff.insert(ans);  // Inserting the character into the buffer 
			if (ans != 'A' && ans != 'E' && ans != 'I' && ans != 'O' && ans != 'U'){
				numGConso = numGConso + 1;  // incereasing the counter if its a cononant
			}
			String s = String.format("\033[0;4m[Generator %d]: inserted %s at index %d at time\033[0;0m %s", id, ans, index, Coordinator.getTime());
            System.out.println(s);
			count--;
        }
	
	}
	public int getGConsonents(){
		return numGConso;
	}
}
