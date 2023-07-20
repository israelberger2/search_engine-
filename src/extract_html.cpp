#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <string>

#include "extract_html.hpp"
#include "se_exceptions.hpp"


namespace se{

std::string extract_html(const std::string& url)
{
  curlpp::Cleanup cleanup;
  curlpp::Easy request;
  std::ostringstream htmlContent;
  
  request.setOpt(curlpp::options::Url(url));
  request.setOpt(curlpp::options::WriteStream(&htmlContent));

  try{
    request.perform();
    std::string htmlString = htmlContent.str();
    return htmlString;
    
  } catch (const curlpp::RuntimeError& error){
    throw HtmlExcaption(std::string("ERROR: curlpp::runtime_error: ") + error.what());     
  }
}
     

} // namespace se
