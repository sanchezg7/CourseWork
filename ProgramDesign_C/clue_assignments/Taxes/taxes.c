/* In-Class Programming Assignment - Taxes */
/* Author: Gerardo Sanchez   */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i = 0, num_clients = 0, client_id = 0, depend = 0;
  double gross = 0.0, net = 0.0, taxable = 0.0, tax = 0.0, effective = 0.0;
  /*prompt for client number
  printf("Enter number of clients:");*/
  scanf("%d", &num_clients);

  for(i = num_clients; i>=1; --i)
  {
  /*ask for id, gross and # of dependents
  	printf("Client ID, Gross, Dependents:");*/
	scanf("%d%lf%d", &client_id, &gross, &depend);
	
	net = (gross) - (1000*depend);
	
	taxable = (net*0.85);
	
	//print net and amount taxable
	//printf("net:%.2f\ntaxable:%.2f\n", net, taxable);

	if(taxable >=35000)
	{
		tax = (1500) + (4000) + ((taxable-35000) * 0.3);
	}
	else{
		if(taxable < 35000 && taxable > 15000)
		{
			tax = (1500) + ((taxable - 15000)*0.2);
		}
		else{
			if(taxable <=15000)		
			tax = taxable * 0.1;
		}
	}
	effective = (tax/gross)*100;
	printf("%d\t%.0f\t%.1f\n", client_id, tax, effective);
	
		
	}
	return(0);
}


	
	

