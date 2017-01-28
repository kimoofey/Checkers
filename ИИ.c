if (deep == 0)
return;
int i = 0, b = 0, p = 0, bb = 0, kolvo = 0, bx = 0, by = 0, j = 0, count = 0, busr = 0;
int mx = 0, nx = 0, my = 0, ny = 0, d = 0, d2 = 0, c = 0, kk = 0;
bool q = false;
color bro, enemy;
if (deep % 2 == 0)
{
	bro = white;
	enemy = black;
	kolvo = whites;
}
else
{
	bro = black;
	enemy = white;
	kolvo = blacks;
}
scan(bro, enemy, intel);
for (i = 0; i < kolvo; i++)
{
	busr = -50;
	if (block)
	{
		while (b < 64)
		{
			if (intel[b].lockcut == true && intel[b].queen != true)
			{
				for (p = 0; p < 8; p += 2)
				{
					bx = intel[b].name[0] + period[p] * 50;
					by = intel[b].name[1] + period[p + 1] * 50;
					bb = 0;
					while (bb < 64)
					{
						if (intel[bb].name[0] == bx && intel[bb].name[1] == by)
							break;
						bb++;
					}
					if (intel[bb].shash == enemy && abs(intel[b].name[0] - intel[bb].name[0]) == 50 && abs(intel[b].name[1] - intel[bb].name[1]) == 50)
					{
						busr = bb;
						intel[bb].comp = true;
						intel[bb].shash = quadr;
						if (intel[bb].queen)
						{
							if (intel[bb].shash == white)
								bufvalue += 5;
							else
								bufvalue -= 5;
							q = true;
						}
						else
						{
							if (intel[bb].shash == white)
								bufvalue += 3;
							else
								bufvalue -= 3;
							q = false;
						}
						intel[bb].queen = false;
						if (bb != 64)
						{
							bx = intel[b].name[0] + period[p] * 100;
							by = intel[b].name[1] + period[p + 1] * 100;
							if (bx > 0 && by > 0 && bx < 450 && by < 450)
							{
								bb = 0;
								while (bb < 64)
								{
									if (intel[bb].name[0] == bx && intel[bb].name[1] == by && (intel[bb].shash == empty || intel[bb].shash == quadr))
										break;
									bb++;
								}
								if (bb == 64)
									break;
								intel[bb].shash = intel[b].shash;
								intel[bb].queen = intel[b].queen;
								intel[b].shash = quadr;
								intel[b].queen = false;
								scan(enemy, bro, intel);
								for (j = 0; j < 64; j++)
								{
									if (intel[j].target)
										bufvalue--;
									else
										bufvalue++;
								}
								intelegent(deep - 1);
								intel[b].shash = intel[bb].shash;
								intel[bb].shash = quadr;
								intel[b].queen = intel[bb].queen;
								intel[bb].queen = false;
								intel[busr].comp = true;
								intel[busr].shash = quadr;
								if (q == true)
									intel[busr].queen = true;
							}

						}
					}

				}
			}
			if (intel[b].lockcut == true && intel[b].queen == true)
			{
				for (count = 0; count < 8; count += 2)
				{
					mx = nx = intel[b].name[0];
					my = ny = intel[b].name[1];
					d2 = d = 50;
					while (ny < 450 && nx < 450 && ny > 25 && nx > 25)
					{
						for (c = 0; c < 64; c++)
						{
							if (intel[c].name[0] == intel[b].name[0] + period[count] * d && intel[c].name[1] == intel[b].name[1] + period[count + 1] * d && intel[c].target == true) // Если встречаем жертву
							{
								for (kk = 0; kk < 64; kk++)
								{
									if (intel[c].name[0] + d * period[count] == intel[kk].name[0] && intel[c].name[1] + d * period[count + 1] == intel[kk].name[1] && intel[kk].shash == enemy) // Есть ли за ней препятствие
									{
										mx = 0;
										nx = 500;
										kk = 64;
										c = 65;
									}
								}
								while (my < 450 && mx < 450 && my > 25 && mx >25) // Препятствия нет, теперь ищем куда приземлиться 
								{
									for (j = 0; j < 64; j++)
									{
										if (intel[j].name[0] == intel[c].name[0] + period[count] * d2 && intel[j].name[1] == intel[c].name[1] + period[count + 1] * d2 && intel[j].border == true)
										{
											busr = c;
											intel[c].shash = quadr;
											intel[c].comp = true;
											if (intel[c].queen == true)
											{
												if (intel[c].shash == white)
													bufvalue += 5;
												else
													bufvalue -= 5;
												q = true;
											}
											else
											{
												if (intel[bb].shash == white)
													bufvalue += 3;
												else
													bufvalue -= 3;
												q = false;
											}
											intel[c].queen = false;
											intel[j].shash = intel[b].shash;
											intel[j].queen = intel[b].queen;
											intel[b].shash = quadr;
											intel[b].queen = false;
											scan(bro, enemy, intel);
											for (kk = 0; kk < 64; kk++)
											{
												if (intel[kk].target)
													bufvalue--;
												else
													bufvalue++;
											}
											intelegent(deep - 1);
											intel[b].shash = intel[bb].shash;
											intel[bb].shash = quadr;
											intel[b].queen = intel[bb].queen;
											intel[bb].queen = false;
											intel[busr].shash = quadr;
											intel[busr].comp = true;
											if (q == true)
												intel[busr].queen = true;
										}
									}
									d2 += 50;
									mx = mx + period[count] * 50;
									my = my + period[count + 1] * 50;
								}

							}
						}
						d += 50;
						nx = nx + period[count] * 50;
						ny = ny + period[count + 1] * 50;
					}
				}
			}
			b++;
		}
		break;
	}
	else
	{
		while (intel[b].shash != bro)
		{
			if (b == 64)
				break;
			b++;
		}
		if (b == 64)
			break;
		for (p = 0 + (deep + 1) % 2 * 4; p < 4 + (deep + 1) % 2 * 4; p += 2)
		{
			bx = intel[b].name[0] - period[p] * 50;
			by = intel[b].name[1] - period[p + 1] * 50;
			bb = 0;
			while (bb < 64)
			{
				if (intel[bb].name[0] == bx && intel[bb].name[1] == by)
					break;
				bb++;
			}
			if (intel[bb].shash == quadr || intel[bb].shash == empty)
			{
				intel[bb].shash = intel[b].shash;
				intel[b].shash = quadr;
				intel[bb].queen = intel[b].queen;
				intel[b].queen = false;
				scan(enemy, bro, intel);
				for (j = 0; j < 64; j++)
				{
					if (intel[j].target)
						bufvalue--;
					else
						bufvalue++;
				}
				intelegent(deep - 1);
				intel[b].shash = intel[bb].shash;
				intel[bb].shash = quadr;
				intel[b].queen = intel[bb].queen;
				intel[bb].queen = false;
				scan(bro, enemy, intel);
			}
		}
	}
	b++;
}