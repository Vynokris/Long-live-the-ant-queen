from PIL import Image
import os

alphabet = ["a", "b", "c",
            "d", "e", "f", "g",
            "h", "i", "j", "k",
            "l", "m", "n", "o",
            "p", "q", "r", "s",
            "t", "u", "v", "w",
            "x", "y", "z", None,
            None, None, None, None,
            None, None, None, None,
            None, None, "Cntrl", "Shift",
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
            None, None, "Space", None,
            None, "Tab", None, None,
            None, None, None, None,
            None, None, None, None,
            "ArrowLeft", "ArrowRight", "ArrowUp", "ArrowDown"]

for i in range(len(alphabet)):
    try:
        if not alphabet[i] is None:
            key_image = Image.open("C:/Users/remis/CppProjects/Long Live The Ant Queen/Long Live The Ant Queen/Resources/Raw art resources/Kadith's free icons/" + alphabet[i] + "RetroBlack.png")

            if alphabet[i] == "Space":
                key_image = key_image.crop((0, 0, 80, 16))
            elif alphabet[i] == "Cntrl":
                key_image = key_image.crop((0, 0, 20, 16))
            elif alphabet[i] == "Shift":
                key_image = key_image.crop((0, 0, 24, 16))
            elif alphabet[i] == "Tab":
                key_image = key_image.crop((0, 0, 27, 16))
            else:
                key_image = key_image.crop((0, 0, 16, 16))

            #key_image.save(str(i)+".png")

            os.remove(str(i) + "_Hover.png")

            """
            if i < 26:
                os.remove(alphabet[i].upper()+"RetroBlack.png")
            else:
                os.remove(alphabet[i] + "RetroBlack.png")"""

    except Exception as error:
        print(error)