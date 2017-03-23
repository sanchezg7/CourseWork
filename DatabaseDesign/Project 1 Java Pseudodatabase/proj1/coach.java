public class coach {
	
	public String getID() {
		return this.ID;
	}
	
	public String getFirst(){
		return this.first;
	}
	
	public String getLast(){
		return this.last;
	}
	
	public long getseasonWin(){
		return this.seasonWin;
	}
	
	public long getseasonLoss(){
		return this.seasonLoss;
	}
	
	public long getPlayOffWin(){
		return this.playoffWin;
	}
	
	public long getPlayOffLoss(){
		return this.playoffLoss;
	}
	
	public String getTeam(){
		return this.team;
	}
	

	private String ID;
	private String first;
	private String last;
	private long seasonWin;
	private long seasonLoss; 
	private long playoffWin; //cannot be negative but prevent user from inputting negative int
	private long playoffLoss;
	private String team;
}