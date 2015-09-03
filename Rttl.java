
public class Rttl{

	private static final double BASE_OCTAVE [] = {440.0,466.0,494.0,523.0,554.0,587.0,622.0,659.0,698.0,740.0,784.0,830.0};
	private static final int OCTAVES = 4;
	private static final String NOTE_NAME [] = {"a","Bb","h","c","Db","d","Eb","e","f","Gb","g","Ab"};
	private static final double FOSC = 12.0; //Mhz
	private static final int PRESCALER = 4;
	private static final int INVERSE = 1000000; //conversão de us
	private static double timerClkPeriod;
	
	
	private static int getTimerCmpValue(double frequency){
		return (int)(INVERSE / (frequency*timerClkPeriod * 2));	// ciclo de 2 clock's
	}
	
	private static void getRoundFreqFromTimer1(){	
		for(int i = 1; i < 65536; i++){
			double freq = (INVERSE/2)/(timerClkPeriod*i);
			if((freq % 1000) == 0)
				System.out.println("Round frequency "+freq+ "Hz tick value " + i);
		}
	
	}
	 
	public static void main(String [] argv){
		String name;
		int [] timerValues = new int[BASE_OCTAVE.length*OCTAVES];
		
		timerClkPeriod = 1 / (FOSC/(4*PRESCALER));
		System.out.println("Clock period "+timerClkPeriod+"us");
		for(int oc = 0; oc < 4; oc++){			
			for(int i = 0; i < BASE_OCTAVE.length; i++){
				name = NOTE_NAME[i] + (oc==0? "":oc+4);
				int tmp = (oc*BASE_OCTAVE.length) + i;
				timerValues[tmp] = getTimerCmpValue( (1<<oc) * BASE_OCTAVE[i]);;
				//System.out.println("#define "+name+"\t" + tmp + "\t/* note freq: " + (1<<oc) * BASE_OCTAVE[i]+"Hz */" );
				System.out.println("#define "+name+"\t" + (tmp+1) + "\t/* note freq: " + (1<<oc) * BASE_OCTAVE[i]+"Hz */" );
			}
		}
		System.out.println("#define p\t0\t/* pause */");
		System.out.println("const int cmp_values[]={0,");
		for(int i = 0; i < BASE_OCTAVE.length*OCTAVES; i++){
			System.out.print(timerValues[i]+",");
		}
		System.out.println("\n};");
		
		getRoundFreqFromTimer1();
	}
}