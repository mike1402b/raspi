<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Datum und Uhrzeit</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            margin: 0;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        }
        .container {
            background: white;
            padding: 40px;
            border-radius: 10px;
            box-shadow: 0 10px 25px rgba(0,0,0,0.2);
            text-align: center;
        }
        h1 {
            color: #333;
            margin-bottom: 20px;
        }
        .datetime {
            font-size: 24px;
            color: #667eea;
            font-weight: bold;
        }
        .date {
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Aktuelles Datum und Uhrzeit</h1>
        <div class="datetime">
            <div class="date">
                <?php echo date('d.m.Y'); ?>
            </div>
            <div class="time">
                <?php echo date('H:i:s'); ?>
            </div>
        </div>
    </div>
</body>
</html>
