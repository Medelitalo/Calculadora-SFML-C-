#include <SFML/Graphics.hpp>	
#include <iostream>
#include <vector>

// 21 digitos 
// EStrutura para representar um botão 

struct Button{
	sf::RectangleShape Shape; 
	sf::Text text; 
};

//função para realizar a operação matematica 
float realizarOperacao(float operando1, float operando2, char operador) {
	switch (operador)
	{
	case '+':
		return operando1 + operando2; 
	case '-':
		return operando1 - operando2; 
	case '*':
		return operando1 * operando2; 
	case '/':
		if (operando2 != 0)
		{
			return operando1 / operando2; 
		}
		else
		{
			return NAN; // retorna NaN ( not a Number) em caso de divisao por 0 
		}
	default:
		return NAN; // operador invalido 
	}
}



int main() {
	sf::RenderWindow Janela(sf::VideoMode(300, 400), "Janela Principal");

	sf::Font fonte; 

	

	
	//criar font
	sf::Font font; 
	if (!font.loadFromFile("Fonte\\arial.ttf")) {
		std::cerr << "Erro ao carregar a Fonte" << std::endl; 
		return 1; 
	}

	// vetor para armazenar os botões 
	sf::Vector2f ButtonPosition(20.f, 150.f); 
	//Tamanho dos botões 
	sf::Vector2f ButtonSize(50.f, 50.f); 
	//vetor para armazenar os botões numericos 
	std::vector<Button> buttons; 

	//vatiavel para armazenar os operandos e operador 
	std::string Operando1 = ""; 
	std::string Operando2 = "";
	char operador; 

	// Tela de entrada 
	sf::Text inputText("", font, 24); 
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(30.f, 30.f); 

	// criar botões numericos 
	for (int i = 0; i < 10; ++i) {
		Button button; 
		button.Shape.setSize(ButtonSize); 
		button.Shape.setFillColor(sf::Color::White); 
		button.Shape.setPosition(ButtonPosition.x + (i % 3) * (ButtonSize.x + 10.f),
			ButtonPosition.y + (i / 3) * (ButtonSize.y + 10.f)); 

		// texto botão 
		button.text.setFont(font); 
		button.text.setCharacterSize(24); 
		button.text.setFillColor(sf::Color::Black); 
		button.text.setString(std::to_string(i)); // texto botão 
		button.text.setPosition(button.Shape.getPosition().x + 15.f, button.Shape.getPosition().y + 10.f); 
		
		buttons.push_back(button); // adiciona o botão ao vetor buttons 
	}

	//botão de + 
	Button ButtonMais; 
	ButtonMais.Shape.setSize(ButtonSize); 
	ButtonMais.Shape.setFillColor(sf::Color::White); 
	ButtonMais.Shape.setPosition(240.f, 150.f); 
	//fonte 
	ButtonMais.text.setFont(font); 
	ButtonMais.text.setCharacterSize(24); 
	ButtonMais.text.setFillColor(sf::Color::Black); 
	ButtonMais.text.setString("+"); //texto 
	ButtonMais.text.setPosition(ButtonMais.Shape.getPosition().x + 15.f, ButtonMais.Shape.getPosition().y + 10.f); 

	buttons.push_back(ButtonMais); 

	// botão C / limpeza
	Button ButtonC; 
	ButtonC.Shape.setSize(ButtonSize); 
	ButtonC.Shape.setFillColor(sf::Color::White); 
	ButtonC.Shape.setPosition(240.f, 95.f); 
	//fonte 
	ButtonC.text.setFont(font); 
	ButtonC.text.setCharacterSize(24); 
	ButtonC.text.setFillColor(sf::Color::Black); 
	ButtonC.text.setString("c"); // texto
	ButtonC.text.setPosition(ButtonC.Shape.getPosition().x + 15.f, ButtonC.Shape.getPosition().y + 10.f); 

	buttons.push_back(ButtonC); 


	//botão de - 
	Button ButtonMenos; 
	ButtonMenos.Shape.setSize(ButtonSize); 
	ButtonMenos.Shape.setFillColor(sf::Color::White); 
	ButtonMenos.Shape.setPosition(240.f, 205.f);
	//fonte
	ButtonMenos.text.setFont(font); 
	ButtonMenos.text.setCharacterSize(24); 
	ButtonMenos.text.setFillColor(sf::Color::Black); 
	ButtonMenos.text.setString("-"); //texto 
	ButtonMenos.text.setPosition(ButtonMenos.Shape.getPosition().x + 15.f, ButtonMenos.Shape.getPosition().y + 10.f); 
	buttons.push_back(ButtonMenos); 


	//botão de = 
	Button buttonigual; 
	buttonigual.Shape.setSize(ButtonSize); 
	buttonigual.Shape.setFillColor(sf::Color::White); 
	buttonigual.Shape.setPosition(240.f, 260.f); 
	//fonte
	buttonigual.text.setFont(font);
	buttonigual.text.setCharacterSize(24); 
	buttonigual.text.setFillColor(sf::Color::Black); 
	buttonigual.text.setString("="); //texto 
	buttonigual.text.setPosition(buttonigual.Shape.getPosition().x + 15.f, buttonigual.Shape.getPosition().y + 10.f); 
	buttons.push_back(buttonigual); 

	// botão de divisão 
	Button buttondiv; 
	buttondiv.Shape.setSize(ButtonSize); 
	buttondiv.Shape.setFillColor(sf::Color::White); 
	buttondiv.Shape.setPosition(240.f, 315.f); 
	//fonte 
	buttondiv.text.setFont(font); 
	buttondiv.text.setCharacterSize(24); 
	buttondiv.text.setFillColor(sf::Color::Black); 
	buttondiv.text.setString("/"); //texto 
	buttondiv.text.setPosition(buttondiv.Shape.getPosition().x + 15.f, buttondiv.Shape.getPosition().y + 10.f); 
	buttons.push_back(buttondiv); 

	// tela de numero e resultado 
	sf::RectangleShape TelaResut;
	sf::Text TextTela;
	TelaResut.setSize(sf::Vector2f(270.f, 50.f));//tamanho do retanguo
	TelaResut.setPosition(15.f, 20.f);
	TelaResut.setFillColor(sf::Color::White);
	//fonte
	TextTela.setFont(font); 
	TextTela.setCharacterSize(24); 
	TextTela.setFillColor(sf::Color::Black); 
	TextTela.setPosition(100.f, 30.f); 

	

	//Loop Principal 
	while (Janela.isOpen()) {
		
		//Verificar Eventos 
		sf::Event Evento; 
		while (Janela.pollEvent(Evento)) {

			// se o evento for de fechar a janela = fechar
			if (Evento.type == sf::Event::Closed)
			{
				Janela.close(); 
			}

			// se o evento for de clique do mouse 
			if (Evento.type == sf::Event::MouseButtonPressed) {
				// verifica se algum botão foi clicado 
				if (Evento.mouseButton.button == sf::Mouse::Left){

					sf::Vector2f mousePos = Janela.mapPixelToCoords(sf::Vector2i(Evento.mouseButton.x, Evento.mouseButton.y)); 
					for ( const Button& button : buttons )
					{
				
						if (button.Shape.getGlobalBounds().contains(mousePos))
						{	
					
							// se o botão for clicado for um numero
							if (button.text.getString().toAnsiString() >= "0" && button.text.getString().toAnsiString() <= "9")
							{
								inputText.setString(inputText.getString() + button.text.getString());
							}
							else if (button.text.getString() == "=")
							{
								 //estrair a expressão da tela de entrada 
								std::string expressao= inputText.getString().toAnsiString();
								size_t posOperador = expressao.find_first_of("+-*/"); 
								float operador1 = std::stof(expressao.substr(0, posOperador)); 
								float operador2 = std::stof(expressao.substr(posOperador + 1)); 
								char operador = expressao[posOperador]; 
								
								//realiza a operação 
								float resultado = realizarOperacao(operador1, operador2, operador); 

								//exibir o resultado na tela 
								inputText.setString(std::to_string(resultado)); 

							}
							else if (button.text.getString() == "c") {

								// limpar a tela de resultado 
								inputText.setString(""); 
							}
							else {
								inputText.setString(inputText.getString() + " " + button.text.getString() + " "); 
							}
							// se o botão clicado for um operador 
							//else
						//	{
							//	Operando1 = inputText.getString(); 
							//	operador = button.text.getString().toAnsiString()[0]; 
							//	inputText.setString(inputText.getString() + " " + button.text.getString() + " ");
							//}

						}
					}
				}
			}
		}

	
		//Limpar Janela 
		//Janela.clear(); 
		Janela.clear(sf::Color(96, 96, 96));
		Janela.draw(TelaResut);
		Janela.draw(inputText);
	 

		for (const Button& button : buttons )
		{

			Janela.draw(button.Shape); 
			Janela.draw(button.text);
			
			
		}
		
		Janela.display(); 
	}
	
	return 0; 
}