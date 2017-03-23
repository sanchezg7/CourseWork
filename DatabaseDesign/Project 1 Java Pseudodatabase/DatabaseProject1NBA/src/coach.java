public class coach {
	
	public coach (String tempID, String tempSeason, String tempFirst, String tempLast, String stempWin, String stempLoss,
					String ptempWin, String ptempLoss, String team) {
		this.setID(tempID);
		this.setSeasonYear(tempSeason);
		this.setFirst(tempFirst);
		this.setLast(tempLast);
		this.setSeasonWin(stempWin);
		this.setSeasonLoss(stempLoss);
		this.setPlayOffWin(ptempWin);
		this.setPlayOffLoss(ptempLoss);
		this.setTeam(team);
		
		return;
	}
	  
	public static boolean anyEqual(coach c1, coach c2){
		
		//if any are equal then it returns true
		if ((c1.getID().equals(c2.getID())) ||					//compares ID  
			(c1.getSeasonYear().equals(c2.getSeasonYear())) ||	//compares season year
			(c1.getFirst().equals(c2.getFirst())) ||			//compares First name				
			(c1.getLast().equals(c2.getLast())) ||				//compares Last name
			(c1.getseasonWin().equals(c2.getseasonWin())) ||	//compares Season Wins
			(c1.getseasonLoss().equals(c2.getseasonLoss())) ||	//compares Season Loss
			(c1.getPlayOffWin().equals(c2.getPlayOffWin())) ||	//compares Playoff Wins
			(c1.getPlayOffLoss().equals(c2.getPlayOffLoss())) ||//compares Playoff Loss
			(c1.getTeam().equals(c2.getTeam())))				//compares Team name
			{ //if they are equal
				return true;
		}else {
			return false;
		}
	}
	
	//set functions
	public void setID(String tempID){
		this.ID = tempID;
		return;
	}
	public void setSeasonYear(String tempSeason){
		this.seasonYear = tempSeason;
	}
	public void setFirst(String tempFirst){
		this.first = tempFirst;
	}
	public void setLast(String tempLast){
		this.last = tempLast;
		return;
	}
	public void setSeasonWin(String tempWin){
		this.seasonWin = tempWin;
		return;
	}
	public void setSeasonLoss(String tempLoss){
		this.seasonLoss = tempLoss;
		return;
	}
	public void setPlayOffWin(String tempWin){
		this.playoffWin = tempWin;
		return;
	}
	public void setPlayOffLoss(String tempLoss){
		this.playoffLoss = tempLoss;
		return;
	}
	public void setTeam(String team){
		this.team = team;
	}
	
	//get functions
	public String getID() {
		return this.ID;
	}
	public String getSeasonYear(){
		return this.seasonYear;
	}
	public String getFirst(){
		return this.first;
	}
	public String getLast(){
		return this.last;
	}
	public String getseasonWin(){
		return this.seasonWin;
	}
	public String getseasonLoss(){
		return this.seasonLoss;
	}
	public String getPlayOffWin(){
		return this.playoffWin;
	}
	public String getPlayOffLoss(){
		return this.playoffLoss;
	}
	public String getTeam(){
		return this.team;
	}
	
	//special function parse string to int and returns net wins
	public int netWins(){
		int seasonWin = Integer.parseInt(this.seasonWin);
		int seasonLoss = Integer.parseInt(this.seasonLoss);
		int playOffWin = Integer.parseInt(this.playoffWin);
		int playOffLoss = Integer.parseInt(this.playoffLoss);
		
		return ((seasonWin - seasonLoss) + (playOffWin - playOffLoss));
	}
	

	private String ID;
	private String seasonYear;
	private String first;
	private String last;
	private String seasonWin;
	private String seasonLoss; 
	private String playoffWin; //cannot be negative but prevent user from inputting negative int
	private String playoffLoss;
	private String team;
	
	//Parameters in order 0: ID, 1: season, 2:first, 3: last, 4:sWin, 5: sLoss, 6: pWin, 7:, pLoss, 8:team
}