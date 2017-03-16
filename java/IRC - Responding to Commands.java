// Daily Programmer 3-16-16 : https://www.reddit.com/r/dailyprogrammer/comments/4anny5/challenge_258_intermediate_irc_responding_to/
// IRC - Responding to commands
// Author: Ken Figueiredo

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Stack;

public class Mar16 {

	public static class ircClient{
		private Socket socket;
		private BufferedReader in;
		private PrintWriter out;
		private String host, name, user, realName;
		private int portNum;
		private String[] channels;
		private String msg;
		
			public ircClient(String[] args){
				String[] t = args[0].split(":");			
				host = t[0];
				portNum = Integer.parseInt(t[1]);
				name = args[1];
				user = args[2];
				realName = args[3] + " " + args[4];
				channels = args[5].split(",");
				msg = "";
				
				for(int i = 6; i < args.length; i++){
					msg.concat(args[i] + " ");
				}
			}
			
			/** openConnection()
			 * Attempts to open connection from given params
			 * Returns true if connection is successful
			 * Returns false otherwise
			 */
			private boolean openConnection(){
				try {
					socket = new Socket(this.host, this.portNum);
					in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
					out = new PrintWriter(socket.getOutputStream(),true);
				} catch (UnknownHostException e) {
					System.err.println("Unknown host: " + this.host + ":" + this.portNum);
					return false;
				} catch (IOException e) {
					System.err.println("I/O error: " + e.toString());
					return false;
				}				
				return true;
			}
			
			/** sendCredentials()
			 * Sends the crendentials of the user to the server
			 */
			private void sendCredentials(){
				out.println("NICK " + this.name);
				out.println("USER " + this.user + " 0 * :" + realName);				
			}
			
			private void joinChannel(String channel){				
				System.out.println(">JOIN " + channel);
				out.println("JOIN " + channel);	
			}
			
			public String[] getChannels(){
				return this.channels;
			}
			
			public String getNickname(){
				return this.name;
			}
			
			public String getUsername(){
				return this.user;
			}
			
			public String getMsg(){
				return this.msg;
			}
			
			/** getServerMsg()
			 * Attempts to get a message from the server
			 * and returns it.
			 */
			private String getServerMsg() throws IOException{
				return in.readLine();
			}
			
			/** sendMsg(String msg)
			 * Takes the given string and passes it to the server.
			 */
			private void sendMsg(String msg){
				System.out.println("> " + msg);
				out.println(msg);			
			}
			
			private void sendPrivMsg(String serverMsg, String msg){
				if(serverMsg.contains("#")){
					String[] t = serverMsg.split("#");
					sendMsg("PRIVMSG #" + t[1] + " :" + msg);
				}
			}
			
			private String parsePrivMsg(String serverMsg){
				String[] t = serverMsg.split(":");
				String cmd = t[t.length-1];			
				String[] t2 = cmd.split(" ");
				
				int val = doArithmetic(t2,0,0);
				return "The answer is " + val;
			}
			
			private int doArithmetic(String[] eq, int index, int val){
				if(index < eq.length){
					if(eq[index].equalsIgnoreCase("sum")){
						if(!isInteger(eq[index+1]))
							val += doArithmetic(eq, index+1, val);
						
						else if(!isInteger(eq[index+2]))
							val += doArithmetic(eq, index+2, val);
						
						else
							return Integer.parseInt(eq[index+1]) + Integer.parseInt(eq[index+2]);
					}
					
					if(eq[index].equalsIgnoreCase("mult")){
						if(!isInteger(eq[index+1]))
							val += doArithmetic(eq, index+1, val);
						
						else if(!isInteger(eq[index+2]))
							val += doArithmetic(eq, index+2, val);
						
						else
							return Integer.parseInt(eq[index+1]) * Integer.parseInt(eq[index+2]);
					}
					
					doArithmetic(eq,index+1,val);
				}

				return val;
			}
			
			private static boolean isInteger(String str){
				try{
					Integer.parseInt(str);
				}catch(NumberFormatException e){
					return false;
				}catch(NullPointerException e){
					return false;
				}				
				return true;
			}
			
			/** replyPong(String ping)
			 * Takes the given string, which should be the server Ping
			 * and returns a Pong message to the server
			 */
			private void replyPong(String ping){
				String[] msg = ping.split(":");
				sendMsg("PONG :" + msg[1]);
			}
			
			/** closeConnect()
			 * Attempts to close the connection to the server
			 * Returns true if the connection is closed successfully
			 * Returns false otherwise
			 */
			private boolean closeConnection(){
				try {
					socket.close();
					out.close();
					in.close();
				} catch (IOException e) {
					System.err.println("I/O error: " + e.toString());
					return false;
				}
				
				return true;
			}
	}
	
	public static void main(String[] args) throws IOException {
		
		ircClient irc = new ircClient(args);
			irc.openConnection();
			irc.sendCredentials();
			
			String serverMsg;
			String[] channels = irc.getChannels();		
			
			while((serverMsg = irc.getServerMsg()) != null){
				System.out.println(serverMsg);
				
				if(serverMsg.contains("/MOTD")){
					for(int i = 0; i < channels.length; i++)
						irc.joinChannel(channels[i]);									
				}
				
				if(serverMsg.contains(irc.getNickname())){
					if(serverMsg.contains("JOIN")){
						irc.sendPrivMsg(serverMsg, irc.getMsg());
					}
					
					if(serverMsg.contains("PRIVMSG")){
						irc.sendPrivMsg(serverMsg,irc.parsePrivMsg(serverMsg));
					}
				}
				
				if(serverMsg.contains("PING")){					
					irc.replyPong(serverMsg);
				}
			}			
		irc.closeConnection();
	}

}
