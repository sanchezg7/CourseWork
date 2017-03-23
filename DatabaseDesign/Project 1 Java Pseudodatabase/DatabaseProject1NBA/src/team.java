
public class team {
	
	public team(String tempID, String tempLocation, String tempName, String tempLeague){
		this.setID(tempID);
		this.setLocation(tempLocation);
		this.setName(tempName);
		this.setLeague(tempLeague);
		
		
		return;
		
		
	}
	
	//set functions
	public void setID(String tempID){
		this.ID = tempID;
		return;
	}
	public void setLocation(String tempLocation){
		this.location = tempLocation;
	}
	public void setName(String tempName){
		this.name = tempName;
	}
	public void setLeague(String tempLeague){
		this.league = tempLeague;
	}

	//get functions
	public String getID(){
		return this.ID;
	}
	public String getLocation(){
		return this.location;
	}
	public String getName(){
		return this.name;
	}
	public String getLeague(){
		return this.league;
	}
	
	
	private String ID;
	private String location;
	private String name;
	private String league;
	
}
