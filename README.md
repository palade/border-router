    
#Extension to Contiki's Border-router 

###Usage
   Clone the repo on the machine which runs contiki and replace contiki/examples/ipv6/native-border-router with the native-border-router folder from this repo.
   
###Changes made    
1. Retrieve the address of the http-server
 * It retrieves the http-server address 
 * Writes the address to a properties file in the user's home directory 
    
2. Return XML response
 * The request to the root page (i.e., index.html or /) of the server returns an XML response
 * A sample of the XML response can be seen in example-response.xml

3. PropertyReader - parses this file and returns the address

4. Modified slip-config.c to accommodate [getopt() bug on raspberryPi](https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=33876)
