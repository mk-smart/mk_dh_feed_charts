<?php

class dhstream {

    function dhstream($feedid, $streamid, $feedtype, $key) {
       $this->feedid = $feedid;
       $this->streamid = $streamid;
       $this->feedtype = $feedtype;
       $this->key = key;
    } 
   
   function get($limit = 100){
      $s = fsockopen("api.beta.mksmart.org", 443, $errno, $errstr); 
      if(!$s) {
         echo "$errno: $errstr\n"; 
         return false;
      } 

      $url = "/sensors/feeds/$this->feedid/datastreams/$this->streamid/datapoints?limit=$this->limit";
      echo $url."</br/>";

      $request = "GET $url HTTP/1.0\r\nHost: api.beta.mksmart.org\r\n"; 

      if ($this->user) {
         $request .= "Authorization: Basic ".base64_encode("$this->key:")."\r\n"; 
      }

      if($post_data) {
         $request .= "Content-Length: ".strlen($post_data)."\r\n\r\n"; 
         $request .= "$post_data\r\n";
      } 
      else {
         $request .= "\r\n";
      }

      fwrite($s, $request); 
      $response = ""; 

      while(!feof($s)) {
         $response .= fgets($s);
      }

      list($this->headers, $this->body) = explode("\r\n\r\n", $response); 
      return $this->body;
   }
}

?>